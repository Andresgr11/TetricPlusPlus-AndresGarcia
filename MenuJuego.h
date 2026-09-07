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
    Bloque* piezaActual;
    Bolsa bolsa;
    Pila piezaEspera;
    int piezaGridX;
    int piezaGridY;
    int puntos;
    bool gameOver;
    Font fuente;
    Text puntaje;
    Text enEspera;
    Text siguientePieza;
    const float posXInicial = 80.0f;
    const float posYInicial = 280.0f;
    const float tamanoBloque = 48.0f;
    Clock relojCaida;
    float tiempoAcumulado = 0.0f;
    const float velocidadCaida = 0.5f;
public:
    MenuJuego();
    ~MenuJuego();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
    void fijarPieza();
    void limpiarFilas();
    bool comprovarMovimiento(int nuevoX, int nuevoY);
};