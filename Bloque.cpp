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
    orientacion = 0;
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

    if (bloqueDestructor) {
        cubo->setColor(Color::White);
        return;
    }

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
        if (orientacion == 0 || orientacion == 2) {
            matrizForma[0][0] = 1;
            matrizForma[0][1] = 1;
            matrizForma[0][2] = 1;
            matrizForma[0][3] = 1;
        }
        else {
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[2][1] = 1;
            matrizForma[3][1] = 1;
        }
        break;

    case Forma::J:
        if (orientacion == 0) {
            matrizForma[0][0] = 1;
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
        }
        else if (orientacion == 1) {
            matrizForma[0][1] = 1;
            matrizForma[0][2] = 1;
            matrizForma[1][1] = 1;
            matrizForma[2][1] = 1;
        }
        else if (orientacion == 2) {
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
            matrizForma[2][2] = 1;
        }
        else {
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[2][0] = 1;
            matrizForma[2][1] = 1;
        }
        break;

    case Forma::L:
        if (orientacion == 0) {
            matrizForma[0][2] = 1;
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
        }
        else if (orientacion == 1) {
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[2][1] = 1;
            matrizForma[2][2] = 1;
        }
        else if (orientacion == 2) {
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
            matrizForma[2][0] = 1;
        }
        else {
            matrizForma[0][0] = 1;
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[2][1] = 1;
        }
        break;

    case Forma::O:
        matrizForma[0][1] = 1;
        matrizForma[0][2] = 1;
        matrizForma[1][1] = 1;
        matrizForma[1][2] = 1;
        break;

    case Forma::S:
        if (orientacion == 0 || orientacion == 2) {
            matrizForma[0][1] = 1;
            matrizForma[0][2] = 1;
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
        }
        else {
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
            matrizForma[2][2] = 1;
        }
        break;

    case Forma::T:
        if (orientacion == 0) {
            matrizForma[0][1] = 1;
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
        }
        else if (orientacion == 1) {
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
            matrizForma[2][1] = 1;
        }
        else if (orientacion == 2) {
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
            matrizForma[2][1] = 1;
        }
        else {
            matrizForma[0][1] = 1;
            matrizForma[1][0] = 1;
            matrizForma[1][1] = 1;
            matrizForma[2][1] = 1;
        }
        break;

    case Forma::Z:
        if (orientacion == 0 || orientacion == 2) {
            matrizForma[0][0] = 1;
            matrizForma[0][1] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
        }
        else {
            matrizForma[0][2] = 1;
            matrizForma[1][1] = 1;
            matrizForma[1][2] = 1;
            matrizForma[2][1] = 1;
        }
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

void Bloque::rotarDerecha() {
    orientacion = (orientacion + 1) % 4;
    crearForma();
}

void Bloque::rotarIzquierda() {
    orientacion = (orientacion + 3) % 4;
    crearForma();
}

void Bloque::dibujar(RenderWindow& ventana, float posX, float posY, float tamanoBloque)
{
    if (cubo == nullptr) return;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrizForma[i][j] == 1) {
                cubo->setPosition({ posX + j * tamanoBloque, posY + i * tamanoBloque });
                ventana.draw(*cubo);
            }
        }
    }
}