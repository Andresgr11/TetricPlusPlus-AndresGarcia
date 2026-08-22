#include "MenuPuntajes.h"

MenuPuntajes::MenuPuntajes() : titulo(fuente), txtSalir(fuente), mejoresPuntajes{ fuente, fuente, fuente, fuente, fuente, fuente, fuente, fuente, fuente, fuente }
{
	if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
		cerr << "Error al cargar la fuente de texto" << endl;
	}

    titulo.setString("Mejores puntajes");
    titulo.setCharacterSize(36);
    titulo.setPosition({ 450.0f, 100.0f });

    for (int i = 0; i < 10; ++i) {
        mejoresPuntajes[i].setString(to_string(i + 1) + ". --- 0 pts");
        mejoresPuntajes[i].setCharacterSize(22);
        mejoresPuntajes[i].setPosition({ 480.0f, 180.0f + (i * 40.0f) });
    }

    txtSalir.setString("VOLVER");
    txtSalir.setCharacterSize(20);
    txtSalir.setPosition({ 550.0f, 700.0f });

    btnSalir.setSize({ 180.0f, 45.0f });
    btnSalir.setPosition({ 510.0f, 690.0f });
    btnSalir.setFillColor(Color::Red);
}

TipoPantalla MenuPuntajes::procesarEvento(const Event & evento, const RenderWindow & ventana)
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

void MenuPuntajes::actualizar()
{}

void MenuPuntajes::dibujar(RenderWindow & ventana)
{
    ventana.draw(titulo);
    ventana.draw(btnSalir);
    ventana.draw(txtSalir);

    for (int i = 0; i < 10; ++i) {
        ventana.draw(mejoresPuntajes[i]);
    }
}
