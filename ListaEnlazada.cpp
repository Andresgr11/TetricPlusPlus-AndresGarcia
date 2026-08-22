#include "ListaEnlazada.h"
#include <iostream>

using namespace std;

ListaEnlazada::ListaEnlazada() : cabeza(nullptr), tamanoActual(0) {}

ListaEnlazada::~ListaEnlazada() {
    limpiar();
}

void ListaEnlazada::insertarInicio(FilaBloques* v) {
    Nodo* nuevo = new Nodo(v);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    tamanoActual++;
}

void ListaEnlazada::insertarFinal(FilaBloques* v) {
    Nodo* nuevo = new Nodo(v);
    if (estaVacia()) {
        cabeza = nuevo;
    }
    else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    tamanoActual++;
}

void ListaEnlazada::eliminarInicio() {
    if (estaVacia()) {
        cout << "Error: La lista esta vacia." << endl;
        return;
    }
    Nodo* temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp->dato;
    delete temp;
    tamanoActual--;
}

void ListaEnlazada::eliminarEn(int x) {
    if (x < 0 || x >= tamanoActual) {
        cout << "Error: Indice fuera de rango." << endl;
        return;
    }
    if (x == 0) {
        eliminarInicio();
        return;
    }

    Nodo* actual = cabeza;
    for (int i = 0; i < x - 1; ++i) {
        actual = actual->siguiente;
    }

    Nodo* eliminar = actual->siguiente;
    actual->siguiente = eliminar->siguiente;
    delete eliminar->dato;
    delete eliminar;
    tamanoActual--;
}

FilaBloques* ListaEnlazada::obtenerEn(int x) const {
    if (x < 0 || x >= tamanoActual) {
        cout << "Error: Indice fuera de rango." << endl;
        return nullptr;
    }
    Nodo* actual = cabeza;
    for (int i = 0; i < x; ++i) {
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