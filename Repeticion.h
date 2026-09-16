#pragma once
#include "Pantalla.h"
#include "ListaDoble.h"
#include "EstadoJuego.h"

class Repeticion : public Pantalla {
private:
    Font fuente;
    Text titulo;
    Text txtSalir;
    Text txtPuntaje;
    Text txtControles;
    Text txtEnEspera;
    RectangleShape btnSalir;
    Texture fondo;
    Sprite* fondoSprite;
    ListaDoble<EstadoJuego>* historial;
    Clock relojReplay;
    float tiempoPaso = 0.5f;
    float acumuladoPaso = 0.0f;
    bool reproduciendo = true;
    Texture texturaBloque;
    Sprite* cuboSprite;
    const float posXInicial = 80.0f;
    const float posYInicial = 280.0f;
    const float tamanoBloque = 48.0f;

public:
    Repeticion();
    ~Repeticion();
    void cargarHistorial(ListaDoble<EstadoJuego>* listaHistorial);
    TipoPantalla procesarEvento(const Event& evento, const RenderWindow& ventana) override;
    void actualizar() override;
    void dibujar(RenderWindow& ventana) override;
};