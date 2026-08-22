#include "FinPartida.h"

FinPartida::FinPartida() : titulo(fuente), puntajeFinal(fuente), top10(fuente), txtMenuPuntajes(fuente), txtMenuPrincipal(fuente), txtRepeticion(fuente)
{
	if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
		cerr << "Error al cargar la fuente de texto" << endl;
	}

    titulo.setString("Game Over");
    titulo.setCharacterSize(40);
    titulo.setPosition({ 640.0f, 350.0f });

    puntajeFinal.setString("Puntaje: " + puntos);
    puntajeFinal.setCharacterSize(24);
    puntajeFinal.setPosition({ 640.0f, 420.0f });

    top10.setString("Has entrado al top 10!");
    top10.setCharacterSize(28);
    top10.setPosition({ 640.0f, 470.0f });

    txtMenuPuntajes.setString("Tabla de puntajes");
    txtMenuPuntajes.setCharacterSize(20);
    txtMenuPuntajes.setPosition({ 300.0f, 550.0f });

    btnMenuPuntajes.setSize({ 220.0f, 45.0f });
    btnMenuPuntajes.setPosition({ 280.0f, 545.0f });
    btnMenuPuntajes.setFillColor(Color::Blue);

    txtMenuPrincipal.setString("Menu Principal");
    txtMenuPrincipal.setCharacterSize(20);
    txtMenuPrincipal.setPosition({ 560.0f, 550.0f });

    btnMenuPrincipal.setSize({ 220.0f, 45.0f });
    btnMenuPrincipal.setPosition({ 540.0f, 545.0f });
    btnMenuPrincipal.setFillColor(Color::Red);

    txtRepeticion.setString("Ver repeticion");
    txtRepeticion.setCharacterSize(20);
    txtRepeticion.setPosition({ 760.0f, 550.0f });

    btnRepeticion.setSize({ 220.0f, 45.0f });
    btnRepeticion.setPosition({ 740.0f, 545.0f });
    btnRepeticion.setFillColor(Color::Green);

}

TipoPantalla FinPartida::procesarEvento(const Event & evento, const RenderWindow & ventana)
{
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            if (btnMenuPuntajes.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::Puntajes;
            }
            else if (btnMenuPrincipal.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::Menu;
            }
            else if (btnRepeticion.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::Replay;
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void FinPartida::actualizar()
{}

void FinPartida::dibujar(RenderWindow & ventana)
{
    ventana.draw(btnMenuPuntajes);
    ventana.draw(btnMenuPrincipal);
    ventana.draw(btnRepeticion);
    ventana.draw(titulo);
    ventana.draw(puntajeFinal);
    ventana.draw(top10);
    ventana.draw(txtMenuPuntajes);
    ventana.draw(txtMenuPrincipal);
    ventana.draw(txtRepeticion);
}
