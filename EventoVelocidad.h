#pragma once
#include "Evento.h"

class MenuJuego;

class EventoVelocidad : public Evento {
private:
    float nuevaVelocidad;

public:
    EventoVelocidad(float tiempo, float velocidad) : Evento(tiempo), nuevaVelocidad(velocidad) {}
    void ejecutar(MenuJuego& juego) override;
};