#include "ListaDoble.h"
#include <iostream>

using namespace std;

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr), nodoActual(nullptr), tamanoActual(0) {}

ListaDoble::~ListaDoble() {
    limpiar();
}

void ListaDoble::agregarMovimiento(Bloque* valor) {
    if (nodoActual != nullptr && nodoActual->siguiente != nullptr) {
        Nodo* eliminar = nodoActual->siguiente;
        while (eliminar != nullptr) {
            Nodo* temp = eliminar;
            eliminar = eliminar->siguiente;
            delete temp;
            tamanoActual--;
        }
        nodoActual->siguiente = nullptr;
        cola = nodoActual;
    }

    Nodo* nuevoNodo = new Nodo(valor);
    if (estaVacia()) {
        cabeza = cola = nuevoNodo;
    }
    else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
    nodoActual = cola;
    tamanoActual++;
}

bool ListaDoble::puedeDeshacer() const {
    return nodoActual != nullptr && nodoActual->anterior != nullptr;
}

bool ListaDoble::puedeRehacer() const {
    return nodoActual != nullptr && nodoActual->siguiente != nullptr;
}

Bloque* ListaDoble::deshacer() {
    if (!puedeDeshacer()) {
        cout << "No hay movimientos para deshacer." << endl;
        return nullptr;
    }
    nodoActual = nodoActual->anterior;
    return nodoActual->dato;
}

Bloque* ListaDoble::rehacer() {
    if (!puedeRehacer()) {
        cout << "No hay movimientos para rehacer." << endl;
        return nullptr;
    }
    nodoActual = nodoActual->siguiente;
    return nodoActual->dato;
}

void ListaDoble::reiniciarNavegacion() {
    nodoActual = cabeza;
}

Bloque* ListaDoble::obtenerActual() const {
    if (nodoActual == nullptr) {
        return nullptr;
    }
    return nodoActual->dato;
}

int ListaDoble::tamano() const {
    return tamanoActual;
}

bool ListaDoble::estaVacia() const {
    return cabeza == nullptr;
}

void ListaDoble::limpiar() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = cola = nodoActual = nullptr;
    tamanoActual = 0;
}