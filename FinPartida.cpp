#include "FinPartida.h"

FinPartida::FinPartida(const string& nombreJugador, int puntaje) : titulo(fuente), txtJugador(fuente), txtPuntajeFinal(fuente),
txtMensajeTop10(fuente), txtMenuPuntajes(fuente), txtRepeticion(fuente), txtMenuPrincipal(fuente), esTop10(false)
{
    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto" << endl;
    }

    esTop10 = verificarSiEsTop10(puntaje);

    panelFondo.setSize({ 700.0f, 500.0f });
    panelFondo.setPosition({ 190.0f, 390.0f });
    panelFondo.setFillColor(Color(20, 20, 30, 230));
    panelFondo.setOutlineThickness(3.0f);
    panelFondo.setOutlineColor(Color::White);

    titulo.setString("GAME OVER");
    titulo.setCharacterSize(50);
    titulo.setFillColor(Color::Red);
    titulo.setPosition({ 430.0f, 420.0f });

    txtJugador.setString("Jugador: " + nombreJugador);
    txtJugador.setCharacterSize(24);
    txtJugador.setFillColor(Color::White);
    txtJugador.setPosition({ 260.0f, 500.0f });

    txtPuntajeFinal.setString("Puntaje Final: " + to_string(puntaje) + " pts");
    txtPuntajeFinal.setCharacterSize(26);
    txtPuntajeFinal.setFillColor(Color::Cyan);
    txtPuntajeFinal.setPosition({ 260.0f, 540.0f });

    bannerTop10.setSize({ 560.0f, 60.0f });
    bannerTop10.setPosition({ 260.0f, 600.0f });

    if (esTop10) {
        bannerTop10.setFillColor(Color(218, 165, 32));
        bannerTop10.setOutlineThickness(2.0f);
        bannerTop10.setOutlineColor(Color::Yellow);

        txtMensajeTop10.setString("¡FELICIDADES! ENTRASTE AL TOP 10");
        txtMensajeTop10.setCharacterSize(22);
        txtMensajeTop10.setFillColor(Color::Black);
        txtMensajeTop10.setPosition({ 280.0f, 615.0f });
    }
    else {
        bannerTop10.setFillColor(Color(50, 50, 60));
        bannerTop10.setOutlineThickness(1.0f);
        bannerTop10.setOutlineColor(Color(100, 100, 100));

        txtMensajeTop10.setString("Sigue intentandolo para entrar al Top 10");
        txtMensajeTop10.setCharacterSize(20);
        txtMensajeTop10.setFillColor(Color::White);
        txtMensajeTop10.setPosition({ 280.0f, 617.0f });
    }

    btnMenuPuntajes.setSize({ 190.0f, 45.0f });
    btnMenuPuntajes.setPosition({ 230.0f, 760.0f });
    btnMenuPuntajes.setFillColor(Color(70, 130, 180));

    txtMenuPuntajes.setString("Puntajes");
    txtMenuPuntajes.setCharacterSize(18);
    txtMenuPuntajes.setPosition({ 280.0f, 770.0f });

    btnRepeticion.setSize({ 190.0f, 45.0f });
    btnRepeticion.setPosition({ 445.0f, 760.0f });
    btnRepeticion.setFillColor(Color(46, 139, 87));

    txtRepeticion.setString("Repeticion");
    txtRepeticion.setCharacterSize(18);
    txtRepeticion.setPosition({ 490.0f, 770.0f });

    btnMenuPrincipal.setSize({ 190.0f, 45.0f });
    btnMenuPrincipal.setPosition({ 660.0f, 760.0f });
    btnMenuPrincipal.setFillColor(Color(178, 34, 34));

    txtMenuPrincipal.setString("Menu Principal");
    txtMenuPrincipal.setCharacterSize(18);
    txtMenuPrincipal.setPosition({ 690.0f, 770.0f });
}

bool FinPartida::verificarSiEsTop10(int puntaje) {
    if (puntaje <= 0) return false;
    vector<RegistroPuntaje> top10 = gestor.obtenerTop10(AlgoritmoOrdenamiento::QuickSort);
    if (top10.size() < 10) return true;
    return puntaje >= top10.back().puntaje;
}

TipoPantalla FinPartida::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            Vector2f posF(posMouse);

            if (btnMenuPuntajes.getGlobalBounds().contains(posF)) {
                return TipoPantalla::Puntajes;
            }
            else if (btnRepeticion.getGlobalBounds().contains(posF)) {
                return TipoPantalla::Replay;
            }
            else if (btnMenuPrincipal.getGlobalBounds().contains(posF)) {
                return TipoPantalla::Menu;
            }
        }
    }
    return TipoPantalla::Ninguna;
}

void FinPartida::actualizar() {}

void FinPartida::dibujar(RenderWindow& ventana)
{
    ventana.draw(panelFondo);
    ventana.draw(titulo);
    ventana.draw(txtJugador);
    ventana.draw(txtPuntajeFinal);
    ventana.draw(bannerTop10);
    ventana.draw(txtMensajeTop10);
    ventana.draw(btnMenuPuntajes);
    ventana.draw(txtMenuPuntajes);
    ventana.draw(btnRepeticion);
    ventana.draw(txtRepeticion);
    ventana.draw(btnMenuPrincipal);
    ventana.draw(txtMenuPrincipal);
}