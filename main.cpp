#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MenuPrincipal.h"
#include "MenuJuego.h"
#include "FinPartida.h"
#include "MenuPuntajes.h"
#include "Repeticion.h"

using namespace sf;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    RenderWindow ventana(VideoMode({ 1080, 1280 }), "Tetric++");
    ventana.setFramerateLimit(60);

    Music musicaTetris;
    if (!musicaTetris.openFromFile("recursos/tetristheme.wav")) {
        return -1;
    }
    musicaTetris.play();
    musicaTetris.setLooping(true);

    Pantalla* pantallaActual = nullptr;
    pantallaActual = new MenuPrincipal();

    ListaDoble<EstadoJuego> historialGuardado;

    while (ventana.isOpen()) {

        while (const auto evento = ventana.pollEvent()) {
            if (evento->is<Event::Closed>()) {
                ventana.close();
            }

            if (pantallaActual != nullptr) {
                TipoPantalla cambio = pantallaActual->procesarEvento(*evento, ventana);

                if (cambio == TipoPantalla::Juego) {
                    delete pantallaActual;
                    pantallaActual = new MenuJuego();
                }
                else if (cambio == TipoPantalla::Menu) {
                    delete pantallaActual;
                    pantallaActual = new MenuPrincipal();
                }
                else if (cambio == TipoPantalla::Salir) {
                    ventana.close();
                }
                else if (cambio == TipoPantalla::GameOver) {
                    MenuJuego* juego = dynamic_cast<MenuJuego*>(pantallaActual);
                    if (juego != nullptr) {
                        historialGuardado = *(juego->getHistorial());
                    }
                    delete pantallaActual;
                    pantallaActual = new FinPartida();
                }
                else if (cambio == TipoPantalla::Puntajes) {
                    delete pantallaActual;
                    pantallaActual = new MenuPuntajes();
                }
                else if (cambio == TipoPantalla::Replay) {
                    delete pantallaActual;
                    Repeticion* pantallaReplay = new Repeticion();
                    pantallaReplay->cargarHistorial(&historialGuardado);
                    pantallaActual = pantallaReplay;
                }
            }
        }

        if (pantallaActual != nullptr) {
            pantallaActual->actualizar();
        }

        ventana.clear(Color(20, 20, 20));

        if (pantallaActual != nullptr) {
            pantallaActual->dibujar(ventana);
        }
        
        ventana.display();
    }

    if (pantallaActual != nullptr) {
        delete pantallaActual;
        pantallaActual = nullptr;
    }
    return 0;
}