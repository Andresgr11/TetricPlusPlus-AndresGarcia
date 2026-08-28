#include "MenuJuego.h"

MenuJuego::MenuJuego() : puntaje(fuente), enEspera(fuente), siguientePieza(fuente), fondoSprite(nullptr)
{
    if (!fondo.loadFromFile("recursos/tablero.png")) {
        cerr << "Error al cargar la textura." << endl;
    }
    fondoSprite = new Sprite(fondo);

    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto." << endl;
    }
    puntos = 0;

    puntaje.setString("Puntaje: " + to_string(puntos));
    puntaje.setCharacterSize(64);
    puntaje.setPosition({ 680.0f, 740.0f });

    enEspera.setString("En espera");
    enEspera.setCharacterSize(32);
    enEspera.setPosition({ 80.0f, 200.0f });

    siguientePieza.setString("Siguiente pieza:");
    siguientePieza.setCharacterSize(32);
    siguientePieza.setPosition({ 600.0f, 80.0f });

	tablero.limpiar();
    for (int i = 0; i < 20; ++i) {
        FilaBloques* nuevaFila = new FilaBloques();
        nuevaFila->rellenarFila();
        tablero.insertarFinal(nuevaFila);
    }
}

TipoPantalla MenuJuego::procesarEvento(const Event & evento, const RenderWindow & ventana)
{
	return TipoPantalla::Ninguna;
}

void MenuJuego::actualizar()
{

}

void MenuJuego::dibujar(RenderWindow & ventana) // Pruebas del tablero
{
    ventana.draw(*fondoSprite);
    float posXInicial = 80.0f;
    float posYInicial = 280.0f;
    float tamanoBloque = 48.0f;

    for (int i = 0; i < tablero.tamano(); i++) {
        FilaBloques* filaActual = tablero.obtenerEn(i);
        if (filaActual == nullptr) continue;

        for (int j = 0; j < 10; j++) {
            Bloque* b = filaActual->columnas[j];
            if (b != nullptr && b->getSprite() != nullptr) {
                float x = posXInicial + (j * tamanoBloque);
                float y = posYInicial + (i * tamanoBloque);
                b->setPosicion(x, y);
                ventana.draw(*(b->getSprite()));
            }
        }
    }
    
    ventana.draw(puntaje);
    ventana.draw(enEspera);
    ventana.draw(siguientePieza);
}