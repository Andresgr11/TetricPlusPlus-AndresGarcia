#include "Repeticion.h"

Repeticion::Repeticion() : titulo(fuente), txtPuntaje(fuente), txtControles(fuente), txtEnEspera(fuente),
historial(nullptr), cuboSprite(nullptr), fondoSprite(nullptr)
{
    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto." << endl;
    }

    if (!texturaBloque.loadFromFile("recursos/bloque1.png")) {
        cerr << "Error al cargar la textura del bloque." << endl;
    }

    if (!fondo.loadFromFile("recursos/fondo.png")) {
        cerr << "Error al cargar la textura del fondo." << endl;
    }

    fondoSprite = new Sprite(fondo);
    cuboSprite = new Sprite(texturaBloque);

    titulo.setString("REPETICION DE PARTIDA");
    titulo.setCharacterSize(34);
    titulo.setPosition({ 320.0f, 30.0f });

    txtEnEspera.setString("En espera");
    txtEnEspera.setCharacterSize(38);
    txtEnEspera.setPosition({ 80.0f, 135.0f });

    txtControles.setString("Controles:\n[ESPACIO] Play / Pausa\n[IZQ] Retroceder\n[DER] Avanzar\n[ESC] Salir");
    txtControles.setCharacterSize(28);
    txtControles.setPosition({ 680.0f, 880.0f });

    txtPuntaje.setString("Puntaje: 0");
    txtPuntaje.setCharacterSize(50);
    txtPuntaje.setPosition({ 700.0f, 1125.0f });
}

Repeticion::~Repeticion()
{
    if (fondoSprite != nullptr) delete fondoSprite; 
    if (cuboSprite != nullptr) delete cuboSprite; 
}

void Repeticion::cargarHistorial(ListaDoble<EstadoJuego>* listaHistorial)
{
    historial = listaHistorial;
    if (historial != nullptr) {
        historial->irAlInicio();
    }
    reproduciendo = true;
    relojReplay.restart();
}

TipoPantalla Repeticion::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (const auto* tecla = evento.getIf<Event::KeyPressed>()) {
        if (historial != nullptr) {
            if (tecla->code == Keyboard::Key::Space) {
                reproduciendo = !reproduciendo;
            }
            else if (tecla->code == Keyboard::Key::Left) {
                historial->deshacer();
            }
            else if (tecla->code == Keyboard::Key::Right) {
                historial->rehacer();
            }
            else if (tecla->code == Keyboard::Key::Escape) {
                return TipoPantalla::GameOver;
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void Repeticion::actualizar()
{
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

void Repeticion::dibujar(RenderWindow& ventana)
{
    if (fondoSprite != nullptr) {
        ventana.draw(*fondoSprite);
    }
    ventana.draw(titulo);
    ventana.draw(txtEnEspera);
    ventana.draw(txtControles);

    if (historial == nullptr || historial->vacia()) return;
    EstadoJuego estadoActual = historial->getActual();

    txtPuntaje.setString("Puntaje: " + to_string(estadoActual.puntos));
    ventana.draw(txtPuntaje);

    if (estadoActual.tienePiezaEspera) {
        Bloque piezaEsperaObj(estadoActual.piezaEsperaForma);
        piezaEsperaObj.dibujar(ventana, 150.0f, 195.0f, tamanoBloque);
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