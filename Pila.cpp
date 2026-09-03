#include "Pila.h"
#include <iostream>

using namespace std;

Pila::Pila() : topeNodo(nullptr), tamanoActual(0) {}

Pila::~Pila() {
    limpiar();
}

void Pila::apilar(Bloque* v) {
    if (estaVacia()) {
        Nodo* nuevoNodo = new Nodo(v);
        nuevoNodo->siguiente = topeNodo;
        topeNodo = nuevoNodo;
        tamanoActual++;
        return;
    }
    cout << "Pila llena" << endl;
}

Bloque* Pila::desapilar() {
    if (estaVacia()) {
        cout << "Error: La pila esta vacia." << endl;
    }
    Nodo* temporal = topeNodo;
    Bloque* enviar = topeNodo->dato;
    topeNodo = topeNodo->siguiente;
    tamanoActual--;    
    delete temporal; 
    return enviar;
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

void Pila::dibujar(RenderWindow& ventana, float posX, float posY)
{
    if (estaVacia()) return;
    topeNodo->dato->dibujar(ventana, posX, posY);
}
