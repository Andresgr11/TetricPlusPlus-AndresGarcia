#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace sf;

enum class Forma { I, J, L, O, S, T, Z };

class Bloque {
protected:
    Forma forma;
    Texture textura;
    Sprite* cubo;

public:
    Bloque(Forma formaInicial, const string& rutaTextura = "recursos/bloque1.png");
    ~Bloque();
    Forma getForma() const;
    Sprite* getSprite() const;
    void setForma(Forma nuevaForma);
    Forma aleatoria();
    void aplicarColor();
    void setPosicion(float x, float y);
};
