#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"

using namespace sf;

int main() {
    RenderWindow ventana(VideoMode({ 800, 600 }), "Tetric++");
    ventana.setFramerateLimit(60);

    Pantalla* pantallaActual = new MenuPrincipal();

    while (ventana.isOpen()) {

        while (const auto evento = ventana.pollEvent()) {
            if (evento->is<Event::Closed>()) {
                ventana.close();
            }

            if (pantallaActual != nullptr) {
                TipoPantalla cambio = pantallaActual->procesarEvento(*evento, ventana);

                if (cambio == TipoPantalla::Juego) {
                    delete pantallaActual;
                }
                else if (cambio == TipoPantalla::Menu) {
                    delete pantallaActual;
                    pantallaActual = new MenuPrincipal();
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
    delete pantallaActual;
    return 0;
}