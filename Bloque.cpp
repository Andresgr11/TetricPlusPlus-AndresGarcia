#include "Bloque.h"

Bloque::Bloque(Forma formaInicial, const string& rutaTextura) : cubo(nullptr), forma(formaInicial) {
    if (!textura.loadFromFile(rutaTextura)) {
        cerr << "Error al cargar la textura del bloque: " << rutaTextura << endl;
    }
    cubo = new Sprite(textura);
    crearForma();
    aplicarColor();
}

Bloque::~Bloque() {
    if (cubo != nullptr) {
        delete cubo;
        cubo = nullptr;
    }
}

Forma Bloque::getForma() const
{
    return forma;
}

Sprite* Bloque::getSprite() const {
    return cubo;
}

void Bloque::setForma(Forma nuevaForma)
{
    forma = nuevaForma;
    crearForma();
    aplicarColor();
}

Forma Bloque::aleatoria()
{
    int numeroAleatorio = rand() % 7;
    return static_cast<Forma>(numeroAleatorio);
}

void Bloque::aplicarColor()
{
    if (cubo == nullptr) return;

    switch (forma) {
    case Forma::I: cubo->setColor(Color::Cyan); break;
    case Forma::J: cubo->setColor(Color::Blue); break;
    case Forma::L: cubo->setColor(Color::Magenta); break;
    case Forma::O: cubo->setColor(Color::Yellow); break;
    case Forma::S: cubo->setColor(Color::Green); break;
    case Forma::T: cubo->setColor(Color(128, 0, 128)); break;
    case Forma::Z: cubo->setColor(Color::Red); break;
    }
}

void Bloque::crearForma()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrizForma[i][j] = 0;
        }
    }

    switch (forma) {
    case Forma::I:
        matrizForma[0][0] = 1;
        matrizForma[0][1] = 1;
        matrizForma[0][2] = 1;
        matrizForma[0][3] = 1;
        break;
    case Forma::J:
        matrizForma[0][0] = 1;
        matrizForma[1][0] = 1;
        matrizForma[1][1] = 1;
        matrizForma[1][2] = 1;
        break;
    case Forma::L:
        matrizForma[0][2] = 1;
        matrizForma[1][0] = 1;
        matrizForma[1][1] = 1;
        matrizForma[1][2] = 1;
        break;
    case Forma::O:
        matrizForma[0][1] = 1;
        matrizForma[0][2] = 1;
        matrizForma[1][1] = 1;
        matrizForma[1][2] = 1;
        break;
    case Forma::S:
        matrizForma[0][1] = 1;
        matrizForma[0][2] = 1;
        matrizForma[1][0] = 1;
        matrizForma[1][1] = 1;
        break;
    case Forma::T:
        matrizForma[0][1] = 1;
        matrizForma[1][0] = 1;
        matrizForma[1][1] = 1;
        matrizForma[1][2] = 1;
        break;
    case Forma::Z:
        matrizForma[0][0] = 1;
        matrizForma[0][1] = 1;
        matrizForma[1][1] = 1; 
        matrizForma[1][2] = 1;
        break;
    }
}

int Bloque::getCelda(int fila, int col) const
{
    if (fila >= 0 && fila < 4 && col >= 0 && col < 4) {
        return matrizForma[fila][col];
    }
    return 0;
}

void Bloque::dibujar(RenderWindow& ventana, float posX, float posY, float tamanoBloque)
{
    if (cubo == nullptr) return;

    for (int fila = 0; fila < 4; ++fila) {
        for (int col = 0; col < 4; ++col) {
            if (matrizForma[fila][col] == 1) {
                cubo->setPosition({ posX + col * tamanoBloque, posY + fila * tamanoBloque });
                ventana.draw(*cubo);
            }
        }
    }
}