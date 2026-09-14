#include "EventoBloque.h"
#include "MenuJuego.h"

EventoBloque::EventoBloque(float tiempo) : Evento(tiempo) {}

void EventoBloque::ejecutar(MenuJuego& juego)
{
    juego.activarBloqueDestructor();
    juego.mostrarMensaje("La siguiente pieza es un destructor!");
}