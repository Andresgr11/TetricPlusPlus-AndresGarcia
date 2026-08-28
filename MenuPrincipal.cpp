#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal() : titulo(fuente), txtJugar(fuente), txtSalir(fuente)
{
	if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
		cerr << "Error al cargar la fuente de texto" << endl;
	}
    titulo.setString("Tetric++");
    titulo.setCharacterSize(98);
    titulo.setPosition({ 400.0f, 380.0f });

    txtJugar.setString("Jugar");
    txtJugar.setCharacterSize(48);
    txtJugar.setPosition({ 480.0f, 550.0f });

    txtSalir.setString("Salir");
    txtSalir.setCharacterSize(48);
    txtSalir.setPosition({ 480.0f, 650.0f });

    btnJugar.setSize({ 250.0f, 70.0f });
    btnJugar.setPosition({ 410.0f, 545.0f });
    btnJugar.setFillColor(Color::Blue);

    btnSalir.setSize({ 250.0f, 70.0f });
    btnSalir.setPosition({ 410.0f, 645.0f });
    btnSalir.setFillColor(Color::Red);
}

TipoPantalla MenuPrincipal::procesarEvento(const Event & evento, const RenderWindow & ventana)
{
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            if (btnJugar.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::Juego;
            }
            else if (btnSalir.getGlobalBounds().contains(Vector2f(posMouse))) {
                return TipoPantalla::Salir;
            }
        }
    }

    return TipoPantalla::Ninguna;
}

void MenuPrincipal::actualizar()
{}

void MenuPrincipal::dibujar(RenderWindow & ventana){
    ventana.draw(titulo);
    ventana.draw(btnJugar);
    ventana.draw(txtJugar);
    ventana.draw(btnSalir);
    ventana.draw(txtSalir);
}
