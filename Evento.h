#pragma once

class MenuJuego;

class Evento {
protected:
    float tiempo;

public:
    Evento(float tiempo) : tiempo(tiempo) {}
    virtual ~Evento() {}

    float getTiempo() const { return tiempo; }
    virtual void ejecutar(MenuJuego& juego) = 0;
};