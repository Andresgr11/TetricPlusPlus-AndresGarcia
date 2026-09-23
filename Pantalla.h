#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

enum class TipoPantalla {
    Ninguna,
    Menu,
    Juego,
    GameOver,
    Replay,
    Puntajes,
    Salir
};

class Pantalla {
public:
    virtual ~Pantalla() {}
    virtual TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) = 0;
    virtual void actualizar() = 0;
    virtual void dibujar(RenderWindow& ventana) = 0;
};
