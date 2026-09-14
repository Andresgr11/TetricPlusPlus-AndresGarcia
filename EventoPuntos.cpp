#include "EventoPuntos.h"
#include "MenuJuego.h"

EventoPuntos::EventoPuntos(float tiempo, float duracion) : Evento(tiempo), duracionEfecto(duracion) {}

void EventoPuntos::ejecutar(MenuJuego& juego)
{
    juego.activarPuntosDobles(duracionEfecto);
    juego.mostrarMensaje("Puntos Dobles Activados!");
}