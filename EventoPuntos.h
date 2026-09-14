#pragma once
#include "Evento.h"
class EventoPuntos : public Evento
{
private:
	float duracionEfecto;
public:
	EventoPuntos(float tiempo, float duracion);
	void ejecutar(MenuJuego& juego) override;
};