#pragma once

template <class T>
class ListaDoble {
private:
    struct Nodo {
        T dato;
        Nodo* anterior;
        Nodo* siguiente;
        Nodo(T val) : dato(val), anterior(nullptr), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    Nodo* cola;
    Nodo* nodoActual;
    int tamanoActual;

    void borrarPosteriores(Nodo* desde) {
        Nodo* actual = desde;
        while (actual != nullptr) {
            Nodo* sig = actual->siguiente;
            delete actual;
            tamanoActual--;
            actual = sig;
        }
        if (nodoActual != nullptr) {
            nodoActual->siguiente = nullptr;
            cola = nodoActual;
        }
    }
public:
    ListaDoble() : cabeza(nullptr), cola(nullptr), nodoActual(nullptr), tamanoActual(0) {}

    ~ListaDoble() {
        limpiar();
    }

    int tam() const {
        return tamanoActual;
    }

    bool vacia() const {
        return cabeza == nullptr;
    }

    void limpiar() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = cola = nodoActual = nullptr;
        tamanoActual = 0;
    }

    void insertarFinal(T dato) {
        if (nodoActual != nullptr && nodoActual != cola) {
            borrarPosteriores(nodoActual->siguiente);
        }

        Nodo* nuevo = new Nodo(dato);
        if (vacia()) {
            cabeza = cola = nodoActual = nuevo;
        }
        else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
            nodoActual = nuevo;
        }
        tamanoActual++;
    }

    bool tieneAnterior() const {
        return nodoActual != nullptr && nodoActual->anterior != nullptr;
    }

    T deshacer() {
        if (tieneAnterior()) {
            nodoActual = nodoActual->anterior;
            return nodoActual->dato;
        }
        return getActual();
    }

    bool tieneSiguiente() const {
        return nodoActual != nullptr && nodoActual->siguiente != nullptr;
    }

    T rehacer() {
        if (tieneSiguiente()) {
            nodoActual = nodoActual->siguiente;
            return nodoActual->dato;
        }
        return getActual();
    }

    T getActual() const {
        if (nodoActual != nullptr) {
            return nodoActual->dato;
        }
        return T();
    }

    void irAlInicio() {
        nodoActual = cabeza;
    }

    void irAlFinal() {
        nodoActual = cola;
    }

    ListaDoble(const ListaDoble& otra) : cabeza(nullptr), cola(nullptr), nodoActual(nullptr), tamanoActual(0) {
        Nodo* temp = otra.cabeza;
        while (temp != nullptr) {
            insertarFinal(temp->dato);
            temp = temp->siguiente;
        }
        irAlInicio();
    }

    ListaDoble& operator=(const ListaDoble& otra) {
        if (this != &otra) {
            limpiar();
            Nodo* temp = otra.cabeza;
            while (temp != nullptr) {
                insertarFinal(temp->dato);
                temp = temp->siguiente;
            }
            irAlInicio();
        }
        return *this;
    }
};