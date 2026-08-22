#pragma once
#include "Pantalla.h"
class FinPartida : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text puntajeFinal;
    Text top10;
    Text txtMenuPuntajes;
    RectangleShape btnMenuPuntajes;
    Text txtMenuPrincipal;
    RectangleShape btnMenuPrincipal;
    Text txtRepeticion;
    RectangleShape btnRepeticion;
    String puntos;

public:
    FinPartida();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};

