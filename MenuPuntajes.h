#pragma once
#include "Pantalla.h"
#include "GestorPuntajes.h"

class MenuPuntajes : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text mejoresPuntajes[10];
    Text txtSalir;
    RectangleShape btnSalir;
    RectangleShape btnBubble;
    Text txtBubble;
    RectangleShape btnQuick;
    Text txtQuick;
    Text txtAlgoritmoActivo;
    GestorPuntajes gestor;
public:
    MenuPuntajes();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
    void cargarYMostrarPuntajes(AlgoritmoOrdenamiento algoritmo);
};