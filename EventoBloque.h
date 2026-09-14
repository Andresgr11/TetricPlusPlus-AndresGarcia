#pragma once
#include "Evento.h"

class MenuJuego;

class EventoBloque : public Evento
{
public:
    EventoBloque(float tiempo);
    void ejecutar(MenuJuego& juego) override;
};