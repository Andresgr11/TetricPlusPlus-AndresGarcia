#pragma once
#include "Bloque.h"

class Pila {
private:
    struct Nodo {
        Bloque* dato;
        Nodo* siguiente;
        Nodo(Bloque* val) : dato(val), siguiente(nullptr) {}
    };

    Nodo* topeNodo;
    int tamanoActual;

public:
    Pila();
    ~Pila();

    void apilar(Bloque* valor);
    void desapilar();
    Bloque* tope() const;
    bool estaVacia() const;
    int tamano() const;
    void limpiar();
};