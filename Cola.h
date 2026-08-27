#pragma once
#include <iostream>

using namespace std;

template <class T>
class Cola {
private:
    struct Nodo {
        T* dato;
        Nodo* siguiente;
        Nodo(T* val) : dato(val), siguiente(nullptr) {}
    };
    Nodo* frenteNodo;
    Nodo* atrasNodo;
    int tamanoActual;

public:
    Cola() : frenteNodo(nullptr), atrasNodo(nullptr), tamanoActual(0) {}

    ~Cola() {
        limpiar();
    }

    void encolar(T* v) {
        Nodo* nuevoNodo = new Nodo(v);
        if (estaVacia()) {
            frenteNodo = atrasNodo = nuevoNodo;
        }
        else {
            atrasNodo->siguiente = nuevoNodo;
            atrasNodo = nuevoNodo;
        }
        tamanoActual++;
    }

    void desencolar() {
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

    T* frente() const {
        if (estaVacia()) {
            cout << "Error: Intentando obtener el frente de una cola vacia." << endl;
            return nullptr;
        }
        return frenteNodo->dato;
    }

    bool estaVacia() const {
        return frenteNodo == nullptr;
    }

    int tamano() const {
        return tamanoActual;
    }

    void limpiar() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    T* verEn(int x) const {
        if (x < 0 || x >= tamanoActual) {
            cout << "Error: Indice fuera de rango en la cola." << endl;
            return nullptr;
        }
        Nodo* actual = frenteNodo;
        for (int i = 0; i < x; ++i) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }
};