#include "Bloque.h"

Bloque::Bloque(Forma formaInicial, const string& rutaTextura) : cubo(nullptr), forma(formaInicial) {
    if (!textura.loadFromFile(rutaTextura)) {
        cerr << "Error al cargar la textura del bloque: " << rutaTextura << endl;
    }
    cubo = new Sprite(textura);
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
    case Forma::T: break;
    case Forma::Z: cubo->setColor(Color::Red); break;
    }
}

void Bloque::setPosicion(float x, float y) {
    if (cubo != nullptr) {
        cubo->setPosition({ x, y });
    }
}