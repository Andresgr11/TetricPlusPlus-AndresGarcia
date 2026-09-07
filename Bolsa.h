#pragma once
#include "Cola.h"
#include "Bloque.h"
class Bolsa : public Cola<Bloque*>
{
private:

public:
	Bolsa();
	~Bolsa();
	void rellenarBolsa();
	void dibujar(RenderWindow& ventana, float posX, float posY, float tamanoBloque);
};