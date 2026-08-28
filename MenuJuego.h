#pragma once
#include "Pantalla.h"
#include "ListaEnlazada.h"
#include "ListaDoble.h"
#include "Bloque.h"
#include "Pila.h"
#include "Cola.h"
#include "Bolsa.h"

class MenuJuego : public Pantalla {
private:
    ListaEnlazada tablero;
    Texture fondo;
    Sprite* fondoSprite;
    int puntos;
    Font fuente;
    Text puntaje;
    Text enEspera;
    Text siguientePieza;
public:
    MenuJuego();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};

