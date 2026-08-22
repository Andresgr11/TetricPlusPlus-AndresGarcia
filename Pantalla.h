#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class TipoPantalla {
    Ninguna,
    Menu,
    Juego,
    GameOver,
    Replay,
    Puntajes
};

class Pantalla {
public:
    virtual ~Pantalla() {}
    virtual TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) = 0;
    virtual void actualizar() = 0;
    virtual void dibujar(RenderWindow& ventana) = 0;
};
