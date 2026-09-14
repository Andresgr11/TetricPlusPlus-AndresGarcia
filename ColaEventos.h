#pragma once
#include "Cola.h"
#include "Evento.h"

class ColaEventos : public Cola<Evento*>
{
private:

public:
	ColaEventos();
	~ColaEventos();
	void encolarPorTiempo(Evento* nuevoEvento);
};