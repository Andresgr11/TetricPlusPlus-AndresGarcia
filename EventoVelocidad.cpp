#include "EventoVelocidad.h"
#include "MenuJuego.h"

void EventoVelocidad::ejecutar(MenuJuego& juego)
{
	juego.setVelocidadCaida(nuevaVelocidad);
	juego.mostrarMensaje("Velocidad Aumentada!");
}
