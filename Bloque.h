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
    int matrizForma[4][4];
    int orientacion;
public:
    Bloque(Forma formaInicial, const string& rutaTextura = "recursos/bloque1.png");
    ~Bloque();
    Forma getForma() const;
    Sprite* getSprite() const;
    void setForma(Forma nuevaForma);
    static Forma aleatoria();
    void aplicarColor();
    void crearForma();
    int getCelda(int fila, int col) const;
    void rotarDerecha();
    void rotarIzquierda();
    void dibujar(RenderWindow& ventana, float posX, float posY, float tamanoBloque = 48.0f);
};
