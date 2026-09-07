#include "MenuJuego.h"

MenuJuego::MenuJuego() : puntaje(fuente), enEspera(fuente), siguientePieza(fuente), fondoSprite(nullptr), piezaActual(nullptr),
puntos(0), piezaGridX(3), piezaGridY(0), gameOver(false)
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

    bolsa.rellenarBolsa();
    piezaActual = bolsa.desencolar();
}

MenuJuego::~MenuJuego() {
    if (fondoSprite != nullptr) delete fondoSprite;
    if (piezaActual != nullptr) delete piezaActual;
}

TipoPantalla MenuJuego::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (gameOver) {
        return TipoPantalla::GameOver;
    }

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
                piezaActual = bolsa.desencolar();
            }
            
        }
        else if (keyPressed->code == Keyboard::Key::E)
        {
            if (!piezaEspera.estaVacia()) {             
                piezaActual = piezaEspera.desapilar();
            }
        }
        else if (keyPressed->code == Keyboard::Key::Right)
        {
            if (piezaActual != nullptr) {
                piezaActual->rotarDerecha();
                if (!comprovarMovimiento(piezaGridX, piezaGridY)) {
                    piezaActual->rotarIzquierda();
                }
            }
        }
        else if (keyPressed->code == Keyboard::Key::Left)
        {
            if (piezaActual != nullptr) {
                piezaActual->rotarIzquierda();
                if (!comprovarMovimiento(piezaGridX, piezaGridY)) {
                    piezaActual->rotarDerecha();
                }
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void MenuJuego::actualizar()
{   
    if (gameOver) return;

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

    if (bolsa.estaVacia()) {
        bolsa.rellenarBolsa();
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
    bolsa.dibujar(ventana, 805.0f, 140.0f, tamanoBloque);

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

    limpiarFilas();
    delete piezaActual;
    piezaActual = bolsa.desencolar();
    piezaGridX = 3;
    piezaGridY = 0;

    if (!comprovarMovimiento(piezaGridX, piezaGridY)) {
        gameOver = true;
    }
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