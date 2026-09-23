#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal()
    : titulo(fuente), txtJugar(fuente), txtSalir(fuente),
    lblNombrePrompt(fuente), txtNombreInput(fuente), nombreJugador("")
{
    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto" << endl;
    }

    titulo.setString("Tetric++");
    titulo.setCharacterSize(80);
    titulo.setPosition({ 410.0f, 220.0f });

    lblNombrePrompt.setString("Nombre del Jugador:");
    lblNombrePrompt.setCharacterSize(24);
    lblNombrePrompt.setFillColor(Color::White);
    lblNombrePrompt.setPosition({ 410.0f, 380.0f });

    cajaTexto.setSize({ 260.0f, 45.0f });
    cajaTexto.setPosition({ 410.0f, 420.0f });
    cajaTexto.setFillColor(Color(40, 40, 40));
    cajaTexto.setOutlineThickness(2.0f);
    cajaTexto.setOutlineColor(Color::White);

    txtNombreInput.setString("");
    txtNombreInput.setCharacterSize(22);
    txtNombreInput.setFillColor(Color::Yellow);
    txtNombreInput.setPosition({ 420.0f, 428.0f });

    txtJugar.setString("Jugar");
    txtJugar.setCharacterSize(40);
    txtJugar.setPosition({ 480.0f, 525.0f });

    btnJugar.setSize({ 260.0f, 60.0f });
    btnJugar.setPosition({ 410.0f, 520.0f });
    btnJugar.setFillColor(Color::Blue);

    txtSalir.setString("Salir");
    txtSalir.setCharacterSize(40);
    txtSalir.setPosition({ 480.0f, 625.0f });

    btnSalir.setSize({ 260.0f, 60.0f });
    btnSalir.setPosition({ 410.0f, 620.0f });
    btnSalir.setFillColor(Color::Red);
}

TipoPantalla MenuPrincipal::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            Vector2f posF(posMouse);

            if (cajaTexto.getGlobalBounds().contains(posF)) {
                cajaActiva = true;
                cajaTexto.setOutlineColor(Color::Yellow);
            }
            else {
                cajaActiva = false;
                cajaTexto.setOutlineColor(Color::White);
            }

            if (btnJugar.getGlobalBounds().contains(posF) && !nombreJugador.empty()) {
                return TipoPantalla::Juego;
            }
            else if (btnSalir.getGlobalBounds().contains(posF)) {
                return TipoPantalla::Salir;
            }
        }
    }

    if (const auto* textEntered = evento.getIf<Event::TextEntered>()) {
        if (cajaActiva) {
            uint32_t unicode = textEntered->unicode;

            if (unicode == 8) {
                if (!nombreJugador.empty()) {
                    nombreJugador.pop_back();
                }
            }
            else if (unicode >= 32 && unicode <= 126 && nombreJugador.length() < 12) {
                nombreJugador += static_cast<char>(unicode);
            }
            txtNombreInput.setString(nombreJugador);
        }
    }

    return TipoPantalla::Ninguna;
}

void MenuPrincipal::actualizar() {}

void MenuPrincipal::dibujar(RenderWindow& ventana) {
    ventana.draw(titulo);
    ventana.draw(lblNombrePrompt);
    ventana.draw(cajaTexto);
    ventana.draw(txtNombreInput);
    ventana.draw(btnJugar);
    ventana.draw(txtJugar);
    ventana.draw(btnSalir);
    ventana.draw(txtSalir);
}