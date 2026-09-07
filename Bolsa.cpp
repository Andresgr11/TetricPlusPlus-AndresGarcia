#include "Bolsa.h"

Bolsa::Bolsa() : Cola<Bloque*>()
{

}

Bolsa::~Bolsa()
{
	limpiar();
}

void Bolsa::rellenarBolsa()
{
	for (int i = 0; i < 5;i++) {
		Bloque* pieza = new Bloque(Bloque::aleatoria());
		encolar(pieza);
	}
}

void Bolsa::dibujar(RenderWindow& ventana, float posX, float posY, float tamanoBloque)
{
	float y = 0.0f;

	for (int i = 0; i < tamano(); i++) {
		Bloque* pieza = verEn(i);
		if (pieza != nullptr) {
			pieza->dibujar(ventana, posX, posY + y, tamanoBloque);
		}
		y += tamanoBloque * 3.0f;
	}
}
