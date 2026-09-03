#pragma once
#include "Cola.h"
#include "Bloque.h"
class Bolsa : public Cola<Bloque*>
{
private:
	Bloque* pieza;
public:
	Bolsa();
	~Bolsa();
	void rellenarBolsa();
	void dibujar();
};