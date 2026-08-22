#pragma once
#include "Bloque.h"

class ListaDoble {
private:
    struct Nodo {
        Bloque* dato;
        Nodo* anterior;
        Nodo* siguiente;
        Nodo(Bloque* val) : dato(val), anterior(nullptr), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    Nodo* cola;
    Nodo* nodoActual;
    int tamanoActual;

public:
    ListaDoble();
    ~ListaDoble();

    void agregarMovimiento(Bloque* v);
    bool puedeDeshacer() const;
    bool puedeRehacer() const;
    Bloque* deshacer();
    Bloque* rehacer();
    void reiniciarNavegacion();
    Bloque* obtenerActual() const;

    int tamano() const;
    bool estaVacia() const;
    void limpiar();
};