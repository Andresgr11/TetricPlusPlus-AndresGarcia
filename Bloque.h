#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Bloque {
protected:
    Texture textura;
    Sprite* cubo;

public:
    Bloque(const string& rutaTextura = "recursos/bloque.png");
    virtual ~Bloque();

    virtual Sprite* getSprite() const;
    virtual void setPosicion(float x, float y);
};
