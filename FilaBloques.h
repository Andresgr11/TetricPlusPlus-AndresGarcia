#pragma once
#include "Bloque.h"

struct FilaBloques {
    Bloque* columnas[10];

    FilaBloques() {
        for (int i = 0; i < 10; ++i) {
            columnas[i] = nullptr;
        }
    }

    ~FilaBloques() {
        limpiarFila();
    }

    void limpiarFila() {
        for (int i = 0; i < 10; ++i) {
            if (columnas[i] != nullptr) {
                delete columnas[i];
                columnas[i] = nullptr;
            }
        }
    }

    void rellenarFila() {   // Para pruebas
        for (int i = 0; i < 10; ++i) {
            columnas[i] = nullptr;
            Forma formaAleatoria = static_cast<Forma>(rand() % 7);
            columnas[i] = new Bloque(formaAleatoria);
        }
    }

    bool filaLlena() const {
        for (int i = 0; i < 10; ++i) {
            if (columnas[i] == nullptr) return false;
        }
        return true;
    }
};