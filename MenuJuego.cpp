#include "MenuJuego.h"

MenuJuego::MenuJuego() : puntaje(fuente), enEspera(fuente), siguientePieza(fuente), fondoSprite(nullptr), piezaActual(nullptr),
puntos(0), piezaGridX(3), piezaGridY(0)
{
    if (!fondo.loadFromFile("recursos/tablero.png")) {
        cerr << "Error al cargar la textura." << endl;
    }
    fondoSprite = new Sprite(fondo);

    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto." << endl;
    }

    puntaje.setString("Puntaje: " + to_string(puntos));
    puntaje.setCharacterSize(64);
    puntaje.setPosition({ 680.0f, 740.0f });

    enEspera.setString("En espera");
    enEspera.setCharacterSize(32);
    enEspera.setPosition({ 80.0f, 200.0f });

    siguientePieza.setString("Siguiente pieza:");
    siguientePieza.setCharacterSize(32);
    siguientePieza.setPosition({ 600.0f, 80.0f });

	tablero.limpiar();
    for (int i = 0; i < 20; ++i) {
        FilaBloques* nuevaFila = new FilaBloques();
        tablero.insertarFinal(nuevaFila);
    }
    piezaActual = new Bloque(Bloque::aleatoria());
    bolsa.rellenarBolsa();
}

MenuJuego::~MenuJuego() {
    if (fondoSprite != nullptr) delete fondoSprite;
    if (piezaActual != nullptr) delete piezaActual;
}

TipoPantalla MenuJuego::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (const auto* keyPressed = evento.getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::A)
        {
            if (comprovarMovimiento(piezaGridX - 1, piezaGridY)) {
                piezaGridX--;
            }
        }
        else if (keyPressed->code == Keyboard::Key::D)
        {
            if (comprovarMovimiento(piezaGridX + 1, piezaGridY)) {
                piezaGridX++;
            }
        }
        else if (keyPressed->code == Keyboard::Key::S)
        {
            if (comprovarMovimiento(piezaGridX, piezaGridY + 1)) {
                piezaGridY++;
            }
            else {
                fijarPieza();
            }
        }
        else if (keyPressed->code == Keyboard::Key::Q)
        {
            if (piezaEspera.estaVacia()) {
                piezaEspera.apilar(piezaActual);
                piezaActual = new Bloque(Bloque::aleatoria());
            }
            
        }
        else if (keyPressed->code == Keyboard::Key::E)
        {
            if (!piezaEspera.estaVacia()) {             
                piezaActual = piezaEspera.desapilar();
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void MenuJuego::actualizar()
{   
    tiempoAcumulado += relojCaida.restart().asSeconds();

    if (tiempoAcumulado >= velocidadCaida) {
        if (comprovarMovimiento(piezaGridX, piezaGridY + 1)) {
            piezaGridY++;
        }
        else {
            fijarPieza();
        }
        tiempoAcumulado = 0.0f;
    }
}

void MenuJuego::dibujar(RenderWindow & ventana) // Pruebas del tablero
{
    if (fondoSprite != nullptr) {
        ventana.draw(*fondoSprite);
    }

    for (int i = 0; i < tablero.tamano(); i++) {
        FilaBloques* fila = tablero.obtenerEn(i);
        if (fila == nullptr) continue;

        for (int j = 0; j < 10; j++) {
            Bloque* bloqueCelda = fila->columnas[j];
            if (bloqueCelda != nullptr) {
                float px = posXInicial + j * tamanoBloque;
                float py = posYInicial + i * tamanoBloque;

                Sprite* sprite = bloqueCelda->getSprite();
                if (sprite != nullptr) {
                    sprite->setPosition({ px, py });
                    ventana.draw(*sprite);
                }
            }
        }
    }

    if (piezaActual != nullptr) {
        float px = posXInicial + piezaGridX * tamanoBloque;
        float py = posYInicial + piezaGridY * tamanoBloque;
        piezaActual->dibujar(ventana, px, py, tamanoBloque);
    }

    piezaEspera.dibujar(ventana, 80.0f, 88.0f);
    ventana.draw(puntaje);
    ventana.draw(enEspera);
    ventana.draw(siguientePieza);
}

void MenuJuego::fijarPieza()
{
    if (!piezaActual) return;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piezaActual->getCelda(i, j) == 1) {
                int targetY = piezaGridY + i;
                int targetX = piezaGridX + j;

                if (targetY >= 0 && targetY < 20 && targetX >= 0 && targetX < 10) {
                    FilaBloques* fila = tablero.obtenerEn(targetY);
                    if (fila != nullptr) {
                        fila->columnas[targetX] = new Bloque(piezaActual->getForma());
                    }
                }
            }
        }
    }

    delete piezaActual;
    piezaActual = new Bloque(Bloque::aleatoria());
    piezaGridX = 3;
    piezaGridY = 0;

    limpiarFilas();
}

void MenuJuego::limpiarFilas()
{
    for (int i = 0; i < tablero.tamano(); i++) {
        FilaBloques* fila = tablero.obtenerEn(i);
        if (fila && fila->filaLlena()) {
            tablero.eliminarEn(i);
            tablero.insertarInicio(new FilaBloques());
            puntos += 100;
            puntaje.setString("Puntaje: " + to_string(puntos));
        }
    }
}

bool MenuJuego::comprovarMovimiento(int nuevoX, int nuevoY)
{
    if (!piezaActual) return false;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (piezaActual->getCelda(i, j) == 1) {
                int targetX = nuevoX + j;
                int targetY = nuevoY + i;

                if (targetX < 0 || targetX >= 10 || targetY >= 20) {
                    return false;
                }

                if (targetY >= 0) {
                    FilaBloques* fila = tablero.obtenerEn(targetY);
                    if (fila != nullptr && fila->columnas[targetX] != nullptr) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}