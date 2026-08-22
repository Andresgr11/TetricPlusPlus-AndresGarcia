#pragma once
#include "Pantalla.h"
class Repeticion : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text txtSalir;
    RectangleShape btnSalir;

public:
    Repeticion();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};