#pragma once
#include "Bloque.h"

class Cola {
private:
    struct Nodo {
        Bloque* dato;
        Nodo* siguiente;
        Nodo(Bloque* val) : dato(val), siguiente(nullptr) {}
    };

    Nodo* frenteNodo;
    Nodo* atrasNodo;
    int tamanoActual;

public:
    Cola();
    ~Cola();

    void encolar(Bloque* valor);
    void desencolar();
    Bloque* frente() const;
    bool estaVacia() const;
    int tamano() const;
    void limpiar();
    Bloque* verEn(int indice) const;
};