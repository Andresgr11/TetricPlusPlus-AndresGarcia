#pragma once
#include "Pantalla.h"
#include "GestorPuntajes.h"
#include <string>

using namespace std;

class FinPartida : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text txtJugador;
    Text txtPuntajeFinal;
    Text txtMensajeTop10;
    RectangleShape panelFondo;
    RectangleShape bannerTop10;
    RectangleShape btnMenuPuntajes;
    Text txtMenuPuntajes;
    RectangleShape btnRepeticion;
    Text txtRepeticion;
    RectangleShape btnMenuPrincipal;
    Text txtMenuPrincipal;
    GestorPuntajes gestor;
    bool esTop10;
    bool verificarSiEsTop10(int puntaje);
public:
    FinPartida(const string& nombreJugador = "Jugador", int puntaje = 0);
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};