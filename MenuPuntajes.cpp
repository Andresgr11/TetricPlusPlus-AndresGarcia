#include "MenuPuntajes.h"

MenuPuntajes::MenuPuntajes()
    : titulo(fuente), txtSalir(fuente), txtBubble(fuente), txtQuick(fuente), txtAlgoritmoActivo(fuente),
    mejoresPuntajes{ fuente, fuente, fuente, fuente, fuente, fuente, fuente, fuente, fuente, fuente }
{
    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto" << endl;
    }

    titulo.setString("Mejores Puntajes");
    titulo.setCharacterSize(36);
    titulo.setPosition({ 400.0f, 60.0f });

    btnBubble.setSize({ 200.0f, 50.0f });
    btnBubble.setPosition({ 310.0f, 130.0f });
    btnBubble.setFillColor(Color(70, 130, 180));

    txtBubble.setString("Bubble Sort");
    txtBubble.setCharacterSize(20);
    txtBubble.setPosition({ 340.0f, 142.0f });

    btnQuick.setSize({ 200.0f, 50.0f });
    btnQuick.setPosition({ 570.0f, 130.0f });
    btnQuick.setFillColor(Color(46, 139, 87));

    txtQuick.setString("QuickSort");
    txtQuick.setCharacterSize(20);
    txtQuick.setPosition({ 620.0f, 142.0f });

    txtAlgoritmoActivo.setString("Selecciona un algoritmo para ordenar:");
    txtAlgoritmoActivo.setCharacterSize(20);
    txtAlgoritmoActivo.setFillColor(Color::Yellow);
    txtAlgoritmoActivo.setPosition({ 330.0f, 200.0f });

    for (int i = 0; i < 10; ++i) {
        mejoresPuntajes[i].setString(to_string(i + 1) + ". ---");
        mejoresPuntajes[i].setCharacterSize(22);
        mejoresPuntajes[i].setPosition({ 420.0f, 250.0f + (i * 40.0f) });
    }

    btnSalir.setSize({ 180.0f, 45.0f });
    btnSalir.setPosition({ 450.0f, 680.0f });
    btnSalir.setFillColor(Color::Red);

    txtSalir.setString("VOLVER");
    txtSalir.setCharacterSize(20);
    txtSalir.setPosition({ 500.0f, 690.0f });
}

void MenuPuntajes::cargarYMostrarPuntajes(AlgoritmoOrdenamiento algoritmo) {
    vector<RegistroPuntaje> top10 = gestor.obtenerTop10(algoritmo);

    if (algoritmo == AlgoritmoOrdenamiento::BubbleSort) {
        txtAlgoritmoActivo.setString("Ordenado con: Bubble Sort");
    }
    else {
        txtAlgoritmoActivo.setString("Ordenado con: QuickSort");
    }

    for (int i = 0; i < 10; ++i) {
        if (i < static_cast<int>(top10.size())) {
            mejoresPuntajes[i].setString(to_string(i + 1) + ". " + top10[i].nombre + " - " + to_string(top10[i].puntaje) + " pts");
        }
        else {
            mejoresPuntajes[i].setString(to_string(i + 1) + ". --- 0 pts");
        }
    }
}

TipoPantalla MenuPuntajes::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (const auto* btnMouse = evento.getIf<Event::MouseButtonPressed>()) {
        if (btnMouse->button == Mouse::Button::Left) {
            Vector2i posMouse = Mouse::getPosition(ventana);
            Vector2f posF(posMouse);

            if (btnBubble.getGlobalBounds().contains(posF)) {
                cargarYMostrarPuntajes(AlgoritmoOrdenamiento::BubbleSort);
            }
            else if (btnQuick.getGlobalBounds().contains(posF)) {
                cargarYMostrarPuntajes(AlgoritmoOrdenamiento::QuickSort);
            }
            else if (btnSalir.getGlobalBounds().contains(posF)) {
                return TipoPantalla::GameOver;
            }
        }
    }
    return TipoPantalla::Ninguna;
}

void MenuPuntajes::actualizar() {}

void MenuPuntajes::dibujar(RenderWindow& ventana)
{
    ventana.draw(titulo);
    ventana.draw(btnBubble);
    ventana.draw(txtBubble);
    ventana.draw(btnQuick);
    ventana.draw(txtQuick);
    ventana.draw(txtAlgoritmoActivo);
    for (int i = 0; i < 10; ++i) {
        ventana.draw(mejoresPuntajes[i]);
    }
    ventana.draw(btnSalir);
    ventana.draw(txtSalir);
}