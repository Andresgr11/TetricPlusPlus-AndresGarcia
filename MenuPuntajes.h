#pragma once
#include "Pantalla.h"
class MenuPuntajes : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text mejoresPuntajes[10];
    Text txtSalir;
    RectangleShape btnSalir;

public:
    MenuPuntajes();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};