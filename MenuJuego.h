#pragma once
#include "Pantalla.h"
class MenuJuego : public Pantalla {
private:
    

public:
    MenuJuego();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};

