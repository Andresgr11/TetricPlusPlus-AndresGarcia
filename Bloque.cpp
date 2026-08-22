#include "Bloque.h"

Bloque::Bloque(Color c) : color(c) {}

Bloque::~Bloque() {}

Color Bloque::getColor() const {
    return color;
}

void Bloque::setColor(Color c) {
    color = c;
}