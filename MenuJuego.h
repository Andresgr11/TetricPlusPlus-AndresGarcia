#pragma once
#include "Pantalla.h"
#include "ListaEnlazada.h"
#include "ListaDoble.h"
#include "Bloque.h"
#include "Pila.h"
#include "Bolsa.h"
#include "ColaEventos.h"
#include "EstadoJuego.h"


class MenuJuego : public Pantalla {
private:
    ListaEnlazada tablero;
    ListaDoble<EstadoJuego> replay;
    Texture fondo;
    Sprite* fondoSprite;
    Bloque* piezaActual;
    Bolsa bolsa;
    Pila piezaEspera;
    ColaEventos eventos;
    int piezaGridX;
    int piezaGridY;
    int puntos;
    bool gameOver;
    Font fuente;
    Text puntaje;
    Text enEspera;
    Text siguientePieza;
    Text textoEvento;
    float tiempoMensajeEvento = 0.0f;
    const float posXInicial = 80.0f;
    const float posYInicial = 280.0f;
    const float tamanoBloque = 48.0f;
    Clock relojCaida;
    Clock relojJuego;
    float tiempoAcumulado = 0.0f;
    float velocidadCaida = 0.5f;
    int multiplicadorPuntos = 1;
    float duracionPuntosDobles = 0.0f;
    bool siguienteDestructor = false;
public:
    MenuJuego();
    ~MenuJuego();
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
    void fijarPieza();
    void limpiarFilas();
    bool comprovarMovimiento(int nuevoX, int nuevoY);
    void setVelocidadCaida(float velocidad) { velocidadCaida = velocidad; }
    void mostrarMensaje(const string& mensaje);
    void activarPuntosDobles(float duracion) { multiplicadorPuntos = 2; duracionPuntosDobles = duracion; }
    void activarBloqueDestructor() { siguienteDestructor = true; }
    void destruirFilaCompleta(int filaIndex);
    void registrarEstado();
    ListaDoble<EstadoJuego>* getHistorial() { return &replay; }
};


