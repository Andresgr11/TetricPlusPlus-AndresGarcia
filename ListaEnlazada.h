#pragma once
#include "FilaBloques.h"

class ListaEnlazada {
private:
    struct Nodo {
        FilaBloques* dato;
        Nodo* siguiente;
        Nodo(FilaBloques* val) : dato(val), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    int tamanoActual;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    void insertarInicio(FilaBloques* v);
    void insertarFinal(FilaBloques* v);
    void eliminarInicio();
    void eliminarEn(int x);
    FilaBloques* obtenerEn(int x) const;
    int tamano() const;
    bool estaVacia() const;
    void limpiar();
};
