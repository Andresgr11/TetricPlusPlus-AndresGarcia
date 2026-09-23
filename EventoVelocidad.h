#pragma once
#include "Evento.h"

class MenuJuego;

class EventoVelocidad : public Evento {
private:
    float nuevaVelocidad;
    float duracion;
public:
    EventoVelocidad(float tiempo, float velocidad, float duracion) : Evento(tiempo), duracion(duracion),
        nuevaVelocidad(velocidad) {}
    void ejecutar(MenuJuego& juego) override;
};