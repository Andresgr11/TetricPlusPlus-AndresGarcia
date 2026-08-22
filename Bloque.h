#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Bloque {
protected:
    Color color;

public:
    Bloque(Color c = Color::White);
    virtual ~Bloque();

    virtual Color getColor() const;
    virtual void setColor(Color c);
};
