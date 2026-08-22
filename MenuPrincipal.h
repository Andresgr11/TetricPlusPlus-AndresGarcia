#pragma once
#include "Pantalla.h"

class MenuPrincipal : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text txtJugar;
    Text txtSalir;
    RectangleShape btnJugar;
    RectangleShape btnSalir;
public:
    MenuPrincipal();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};
