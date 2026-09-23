#pragma once
#include "Pantalla.h"
#include <string>

using namespace std;

class MenuPrincipal : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text txtJugar;
    Text txtSalir;
    RectangleShape btnJugar;
    RectangleShape btnSalir;
    Text lblNombrePrompt;
    Text txtNombreInput;
    RectangleShape cajaTexto;
    string nombreJugador;
    bool cajaActiva = false;

public:
    MenuPrincipal();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
    string getNombreJugador() const { return nombreJugador.empty() ? "Jugador" : nombreJugador; }
};