#pragma once
#include "Pantalla.h"

class MenuPrincipal : public Pantalla {
private:
    Font fuente;
    Text titulo;
    RectangleShape botonJugar;
    Text textoBotonJugar;

public:
    MenuPrincipal();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};
