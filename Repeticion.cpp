#include "Repeticion.h"

Repeticion::Repeticion() : titulo(fuente), txtSalir(fuente), txtPuntaje(fuente), txtControles(fuente), txtEnEspera(fuente),
historial(nullptr), cuboSprite(nullptr), fondoSprite(nullptr)
{
    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto" << endl;
    }

    if (texturaBloque.loadFromFile("recursos/bloque1.png")) {
        cuboSprite = new Sprite(texturaBloque);
    }

    if (!fondo.loadFromFile("recursos/tablero.png")) {
        cerr << "Error al cargar la textura del tablero" << endl;
    }

    fondoSprite = new Sprite(fondo);

    titulo.setString("REPETICION DE PARTIDA");
    titulo.setCharacterSize(34);
    titulo.setPosition({ 320.0f, 30.0f });

    txtEnEspera.setString("En espera");
    txtEnEspera.setCharacterSize(28);
    txtEnEspera.setPosition({ 80.0f, 40.0f });

    txtControles.setString("Controles:\n[ESPACIO] Play / Pausa\n[IZQ] Retroceder Paso\n[DER] Avanzar Paso");
    txtControles.setCharacterSize(20);
    txtControles.setPosition({ 580.0f, 280.0f });

    btnSalir.setSize({ 260.0f, 50.0f });
    btnSalir.setPosition({ 580.0f, 430.0f });
    btnSalir.setFillColor(Color::Red);

    txtSalir.setString("Menu Principal");
    txtSalir.setCharacterSize(20);
    txtSalir.setPosition({ 615.0f, 442.0f });

    txtPuntaje.setString("Puntaje: 0");
    txtPuntaje.setCharacterSize(48);
    txtPuntaje.setPosition({ 620.0f, 880.0f });
}

Repeticion::~Repeticion() {
    if (fondoSprite != nullptr) delete fondoSprite; 
    if (cuboSprite != nullptr) delete cuboSprite; 
}

void Repeticion::cargarHistorial(ListaDoble<EstadoJuego>* listaHistorial) {
    historial = listaHistorial;
    if (historial != nullptr) {
        historial->irAlInicio();
    }
    reproduciendo = true;
    relojReplay.restart();
}

TipoPantalla Repeticion::procesarEvento(const Event& evento, const RenderWindow& ventana) {
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            if (btnSalir.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::GameOver;
            }
        }
    }
    if (const auto* tecla = evento.getIf<Event::KeyPressed>()) {
        if (historial != nullptr) {
            if (tecla->code == Keyboard::Key::Space) {
                reproduciendo = !reproduciendo;
            }
            else if (tecla->code == Keyboard::Key::Left) {
                reproduciendo = false;
                historial->deshacer();
            }
            else if (tecla->code == Keyboard::Key::Right) {
                reproduciendo = false;
                historial->rehacer();
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void Repeticion::actualizar() {
    if (historial == nullptr || !reproduciendo) return;

    acumuladoPaso += relojReplay.restart().asSeconds();

    if (acumuladoPaso >= tiempoPaso) {
        if (historial->tieneSiguiente()) {
            historial->rehacer();
        }
        else {
            reproduciendo = false;
        }
        acumuladoPaso = 0.0f;
    }
}

void Repeticion::dibujar(RenderWindow& ventana) {
    if (fondoSprite != nullptr) {
        ventana.draw(*fondoSprite);
    }

    ventana.draw(btnSalir);
    ventana.draw(titulo);
    ventana.draw(txtEnEspera);
    ventana.draw(txtSalir);
    ventana.draw(txtControles);

    if (historial == nullptr || historial->vacia()) return;

    EstadoJuego estadoActual = historial->getActual();

    txtPuntaje.setString("Puntaje: " + to_string(estadoActual.puntos));
    ventana.draw(txtPuntaje);

    if (estadoActual.tienePiezaEspera) {
        Bloque piezaEsperaObj(estadoActual.piezaEsperaForma);
        piezaEsperaObj.dibujar(ventana, 80.0f, 88.0f, tamanoBloque);
    }

    if (cuboSprite != nullptr) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (estadoActual.matrizOcupada[i][j]) {
                    switch (estadoActual.matrizTablero[i][j]) {
                    case Forma::I: cuboSprite->setColor(Color::Cyan); break;
                    case Forma::J: cuboSprite->setColor(Color::Blue); break;
                    case Forma::L: cuboSprite->setColor(Color::Magenta); break;
                    case Forma::O: cuboSprite->setColor(Color::Yellow); break;
                    case Forma::S: cuboSprite->setColor(Color::Green); break;
                    case Forma::T: cuboSprite->setColor(Color(128, 0, 128)); break;
                    case Forma::Z: cuboSprite->setColor(Color::Red); break;
                    }
                    cuboSprite->setPosition({ posXInicial + j * tamanoBloque, posYInicial + i * tamanoBloque });
                    ventana.draw(*cuboSprite);
                }
            }
        }
    }

    Bloque piezaTemp(estadoActual.piezaActualForma);
    for (int r = 0; r < estadoActual.piezaActualRotacion; r++) {
        piezaTemp.rotarDerecha();
    }
    float px = posXInicial + estadoActual.piezaGridX * tamanoBloque;
    float py = posYInicial + estadoActual.piezaGridY * tamanoBloque;
    piezaTemp.dibujar(ventana, px, py, tamanoBloque);
}