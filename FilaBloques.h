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
        for (int i = 0; i < 10; ++i) {
            if (columnas[i] != nullptr) {
                delete columnas[i];
                columnas[i] = nullptr;
            }
        }
    }

    bool filaLlena() const {
        for (int i = 0; i < 10; ++i) {
            if (columnas[i] == nullptr) return false;
        }
        return true;
    }
};