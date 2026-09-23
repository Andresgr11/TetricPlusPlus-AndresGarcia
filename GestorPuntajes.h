#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct RegistroPuntaje {
    string nombre;
    int puntaje;
};

enum class AlgoritmoOrdenamiento { BubbleSort, QuickSort };

class GestorPuntajes {
private:
    string rutaArchivo;
    int particion(vector<RegistroPuntaje>& lista, int bajo, int alto);
    void quickSort(vector<RegistroPuntaje>& lista, int bajo, int alto);

public:
    GestorPuntajes(const string& archivo = "recursos/puntajes.txt");
    vector<RegistroPuntaje> cargarPuntajes();
    void guardarPuntajes(const vector<RegistroPuntaje>& lista);
    void agregarPuntaje(const string& nombre, int puntaje);
    void bubbleSort(vector<RegistroPuntaje>& lista);
    void quickSort(vector<RegistroPuntaje>& lista);
    vector<RegistroPuntaje> obtenerTop10(AlgoritmoOrdenamiento algoritmo = AlgoritmoOrdenamiento::QuickSort);
};