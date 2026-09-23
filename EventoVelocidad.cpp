#include "EventoVelocidad.h"
#include "MenuJuego.h"

void EventoVelocidad::ejecutar(MenuJuego& juego)
{
	juego.activarVelocidadAumentada(nuevaVelocidad, duracion);
	juego.mostrarMensaje("Velocidad Aumentada!");
}
