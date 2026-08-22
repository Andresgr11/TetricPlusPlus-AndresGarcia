#include "Cola.h"
#include <iostream>

using namespace std;

Cola::Cola() : frenteNodo(nullptr), atrasNodo(nullptr), tamanoActual(0) {}

Cola::~Cola() {
    limpiar();
}

void Cola::encolar(Bloque* valor) {
    Nodo* nuevoNodo = new Nodo(valor);
    if (estaVacia()) {
        frenteNodo = atrasNodo = nuevoNodo;
    }
    else {
        atrasNodo->siguiente = nuevoNodo;
        atrasNodo = nuevoNodo;
    }
    tamanoActual++;
}

void Cola::desencolar() {
    if (estaVacia()) {
        cout << "Error: La cola esta vacia." << endl;
        return;
    }
    Nodo* temporal = frenteNodo;
    frenteNodo = frenteNodo->siguiente;
    delete temporal;
    tamanoActual--;

    if (frenteNodo == nullptr) {
        atrasNodo = nullptr;
    }
}

Bloque* Cola::frente() const {
    if (estaVacia()) {
        cout << "Error: Intentando obtener el frente de una cola vacia." << endl;
        return nullptr;
    }
    return frenteNodo->dato;
}

bool Cola::estaVacia() const {
    return frenteNodo == nullptr;
}

int Cola::tamano() const {
    return tamanoActual;
}

void Cola::limpiar() {
    while (!estaVacia()) {
        desencolar();
    }
}

Bloque* Cola::verEn(int indice) const {
    if (indice < 0 || indice >= tamanoActual) {
        cout << "Error: Indice fuera de rango en la cola." << endl;
        return nullptr;
    }
    Nodo* actual = frenteNodo;
    for (int i = 0; i < indice; ++i) {
        actual = actual->siguiente;
    }
    return actual->dato;
}