#include "Repeticion.h"

Repeticion::Repeticion() : titulo(fuente), txtSalir(fuente)
{
	if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
		cerr << "Error al cargar la fuente de texto" << endl;
	}

	titulo.setString("REPETICION");
	titulo.setCharacterSize(40);
	titulo.setPosition({ 640.0f, 350.0f });

	txtSalir.setString("Menu Principal");
	txtSalir.setCharacterSize(20);
	txtSalir.setPosition({ 560.0f, 550.0f });

	btnSalir.setSize({ 220.0f, 45.0f });
	btnSalir.setPosition({ 540.0f, 545.0f });
	btnSalir.setFillColor(Color::Red);
}

TipoPantalla Repeticion::procesarEvento(const Event & evento, const RenderWindow & ventana)
{
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            if (btnSalir.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::GameOver;
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void Repeticion::actualizar()
{}

void Repeticion::dibujar(RenderWindow & ventana)
{
	ventana.draw(btnSalir);
	ventana.draw(titulo);
	ventana.draw(txtSalir);
}
