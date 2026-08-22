#include "ListaEnlazada.h"
#include <iostream>

using namespace std;

ListaEnlazada::ListaEnlazada() : cabeza(nullptr), tamanoActual(0) {}

ListaEnlazada::~ListaEnlazada() {
    limpiar();
}

void ListaEnlazada::insertarInicio(Bloque* valor) {
    Nodo* nuevoNodo = new Nodo(valor);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
    tamanoActual++;
}

void ListaEnlazada::insertarFinal(Bloque* valor) {
    Nodo* nuevoNodo = new Nodo(valor);
    if (estaVacia()) {
        cabeza = nuevoNodo;
    }
    else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    tamanoActual++;
}

void ListaEnlazada::eliminarInicio() {
    if (estaVacia()) {
        cout << "Error: La lista esta vacia." << endl;
        return;
    }
    Nodo* temporal = cabeza;
    cabeza = cabeza->siguiente;
    delete temporal;
    tamanoActual--;
}

void ListaEnlazada::eliminarEn(int indice) {
    if (indice < 0 || indice >= tamanoActual) {
        cout << "Error: Indice fuera de rango." << endl;
        return;
    }
    if (indice == 0) {
        eliminarInicio();
        return;
    }

    Nodo* actual = cabeza;
    for (int i = 0; i < indice - 1; ++i) {
        actual = actual->siguiente;
    }

    Nodo* aEliminar = actual->siguiente;
    actual->siguiente = aEliminar->siguiente;
    delete aEliminar;
    tamanoActual--;
}

Bloque* ListaEnlazada::obtenerEn(int indice) const {
    if (indice < 0 || indice >= tamanoActual) {
        cout << "Error: Indice fuera de rango." << endl;
        return nullptr;
    }
    Nodo* actual = cabeza;
    for (int i = 0; i < indice; ++i) {
        actual = actual->siguiente;
    }
    return actual->dato;
}

int ListaEnlazada::tamano() const {
    return tamanoActual;
}

bool ListaEnlazada::estaVacia() const {
    return cabeza == nullptr;
}

void ListaEnlazada::limpiar() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}