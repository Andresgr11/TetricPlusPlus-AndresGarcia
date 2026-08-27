#pragma once
#include "Pantalla.h"
#include "ListaEnlazada.h"
#include "ListaDoble.h"
#include "Bloque.h"
#include "Pila.h"
#include "Cola.h"

class MenuJuego : public Pantalla {
private:

public:
    MenuJuego();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};

