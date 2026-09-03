#include "Bolsa.h"

Bolsa::Bolsa() : Cola<Bloque*>(), pieza(nullptr)
{

}

Bolsa::~Bolsa()
{

}

void Bolsa::rellenarBolsa()
{
	for (int i = 0; i < 5;i++) {
		pieza = new Bloque(Bloque::aleatoria());
		encolar(pieza);
	}
}

void Bolsa::dibujar()
{}
