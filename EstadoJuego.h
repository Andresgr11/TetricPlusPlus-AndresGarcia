#pragma once
#include "Bloque.h"

struct EstadoJuego {
    Forma matrizTablero[20][10];
    bool matrizOcupada[20][10];
    int puntos;
    int piezaGridX;
    int piezaGridY;
    Forma piezaActualForma;
    int piezaActualRotacion;
    Forma piezaEsperaForma;
    bool tienePiezaEspera;
    Forma bolsa[10];
    int cantidadBolsa;

    EstadoJuego() : puntos(0), piezaGridX(0), piezaGridY(0), piezaActualForma(Forma::I), piezaActualRotacion(0),
        piezaEsperaForma(Forma::I), tienePiezaEspera(false), cantidadBolsa(0)
    {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                matrizTablero[i][j] = Forma::I;
                matrizOcupada[i][j] = false;
            }
        }
        for (int i = 0; i < 10; i++) {
            bolsa[i] = Forma::I;
        }
    }
};