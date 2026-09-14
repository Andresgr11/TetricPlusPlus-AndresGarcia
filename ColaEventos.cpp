#include "ColaEventos.h"

ColaEventos::ColaEventos()
{

}

ColaEventos::~ColaEventos() {
    while (!estaVacia()) {
        Evento* ev = desencolar();
        if (ev != nullptr) {
            delete ev;
        }
    }
}

void ColaEventos::encolarPorTiempo(Evento* nuevoEvento)
{
    if (nuevoEvento == nullptr) return;

    if (estaVacia()) {
        encolar(nuevoEvento);
        return;
    }

    int tam = tamano();
    bool insertado = false;

    for (int i = 0; i < tam; i++) {
        Evento* evActual = desencolar();

        if (!insertado && nuevoEvento->getTiempo() < evActual->getTiempo()) {
            encolar(nuevoEvento);
            insertado = true;
        }
        encolar(evActual);
    }

    if (!insertado) {
        encolar(nuevoEvento);
    }
}