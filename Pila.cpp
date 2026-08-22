#include "Pila.h"
#include <iostream>

using namespace std;

Pila::Pila() : topeNodo(nullptr), tamanoActual(0) {}

Pila::~Pila() {
    limpiar();
}

void Pila::apilar(Bloque* valor) {
    Nodo* nuevoNodo = new Nodo(valor);
    nuevoNodo->siguiente = topeNodo;
    topeNodo = nuevoNodo;
    tamanoActual++;
}

void Pila::desapilar() {
    if (estaVacia()) {
        cout << "Error: La pila esta vacia." << endl;
        return;
    }
    Nodo* temporal = topeNodo;
    topeNodo = topeNodo->siguiente;
    delete temporal;
    tamanoActual--;
}

Bloque* Pila::tope() const {
    if (estaVacia()) {
        cout << "Error: Intentando obtener elemento de una pila vacia." << endl;
        return nullptr;
    }
    return topeNodo->dato;
}

bool Pila::estaVacia() const {
    return topeNodo == nullptr;
}

int Pila::tamano() const {
    return tamanoActual;
}

void Pila::limpiar() {
    while (!estaVacia()) {
        desapilar();
    }
}