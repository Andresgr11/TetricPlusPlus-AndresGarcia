#include "GestorPuntajes.h"

GestorPuntajes::GestorPuntajes(const string& archivo) : rutaArchivo(archivo) {}

vector<RegistroPuntaje> GestorPuntajes::cargarPuntajes() {
    vector<RegistroPuntaje> lista;
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) return lista;

    string nombre;
    int puntaje;
    while (archivo >> nombre >> puntaje) {
        lista.push_back({ nombre, puntaje });
    }
    archivo.close();
    return lista;
}

void GestorPuntajes::guardarPuntajes(const vector<RegistroPuntaje>& lista) {
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) return;

    for (const auto& reg : lista) {
        archivo << reg.nombre << " " << reg.puntaje << "\n";
    }
    archivo.close();
}

void GestorPuntajes::bubbleSort(vector<RegistroPuntaje>& lista) {
    int n = static_cast<int>(lista.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (lista[j].puntaje < lista[j + 1].puntaje) {
                swap(lista[j], lista[j + 1]);
            }
        }
    }
}

int GestorPuntajes::particion(vector<RegistroPuntaje>& lista, int bajo, int alto) {
    int pivote = lista[alto].puntaje;
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (lista[j].puntaje > pivote) {
            i++;
            swap(lista[i], lista[j]);
        }
    }
    swap(lista[i + 1], lista[alto]);
    return i + 1;
}

void GestorPuntajes::quickSort(vector<RegistroPuntaje>& lista, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(lista, bajo, alto);
        quickSort(lista, bajo, pi - 1);
        quickSort(lista, pi + 1, alto);
    }
}

void GestorPuntajes::quickSort(vector<RegistroPuntaje>& lista) {
    if (!lista.empty()) {
        quickSort(lista, 0, static_cast<int>(lista.size()) - 1);
    }
}

void GestorPuntajes::agregarPuntaje(const string& nombre, int puntaje) {
    ofstream archivo(rutaArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << nombre << " " << puntaje << "\n";
        archivo.close();
    }
}

vector<RegistroPuntaje> GestorPuntajes::obtenerTop10(AlgoritmoOrdenamiento algoritmo) {
    vector<RegistroPuntaje> lista = cargarPuntajes();

    if (algoritmo == AlgoritmoOrdenamiento::BubbleSort) {
        bubbleSort(lista);
    }
    else {
        quickSort(lista);
    }

    if (lista.size() > 10) {
        lista.resize(10);
    }
    return lista;
}