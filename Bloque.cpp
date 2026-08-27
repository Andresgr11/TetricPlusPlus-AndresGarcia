#include "Bloque.h"

Bloque::Bloque(const string& rutaTextura) : cubo(nullptr) {
    if (!textura.loadFromFile(rutaTextura)) {
        std::cerr << "Error al cargar la textura del bloque: " << rutaTextura << endl;
    }
    cubo = new Sprite(textura);
}

Bloque::~Bloque() {
    if (cubo != nullptr) {
        delete cubo;
        cubo = nullptr;
    }
}

Sprite* Bloque::getSprite() const {
    return cubo;
}

void Bloque::setPosicion(float x, float y) {
    if (cubo != nullptr) {
        cubo->setPosition({ x, y });
    }
}