#pragma once
#include "Bloque.h"

class ListaEnlazada {
private:
    struct Nodo {
        Bloque* dato;
        Nodo* siguiente;
        Nodo(Bloque* val) : dato(val), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    int tamanoActual;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    void insertarInicio(Bloque* valor);
    void insertarFinal(Bloque* valor);
    void eliminarInicio();
    void eliminarEn(int indice);
    Bloque* obtenerEn(int indice) const;
    int tamano() const;
    bool estaVacia() const;
    void limpiar();
};
