#include "MenuJuego.h"
#include "EventoVelocidad.h"
#include "EventoPuntos.h"
#include "EventoBloque.h"

MenuJuego::MenuJuego(const string& nombre) : nombreJugador(nombre), puntos(0), puntaje(fuente), enEspera(fuente),
siguientePieza(fuente), textoEvento(fuente), txtEventosActivos(fuente), fondoSprite(nullptr), piezaActual(nullptr), piezaGridX(3),
piezaGridY(0), gameOver(false), velocidadCaida(0.5f)
{
    if (!fondo.loadFromFile("recursos/fondo.png")) {
        cerr << "Error al cargar la textura del fondo." << endl;
    }
    fondoSprite = new Sprite(fondo);

    if (!fuente.openFromFile("recursos/tetrisfont.otf")) {
        cerr << "Error al cargar la fuente de texto." << endl;
    }

    enEspera.setString("En espera");
    enEspera.setCharacterSize(38);
    enEspera.setPosition({ 80.0f, 135.0f });

    siguientePieza.setString("Siguiente pieza:");
    siguientePieza.setCharacterSize(42);
    siguientePieza.setPosition({ 400.0f, 120.0f });

    textoEvento.setFont(fuente);
    textoEvento.setCharacterSize(26);
    textoEvento.setFillColor(Color::Yellow);
    textoEvento.setPosition({ 680.0f, 1020.0f });

    txtEventosActivos.setFont(fuente);
    txtEventosActivos.setCharacterSize(22);
    txtEventosActivos.setFillColor(Color::Green);
    txtEventosActivos.setPosition({ 680.0f, 950.0f });

    puntaje.setString("Puntaje: " + to_string(puntos));
    puntaje.setCharacterSize(50);
    puntaje.setPosition({ 700.0f, 1125.0f });

	tablero.limpiar();
    for (int i = 0; i < 20; i++) {
        FilaBloques* nuevaFila = new FilaBloques();
        tablero.insertarFinal(nuevaFila);
    }

    bolsa.rellenarBolsa();
    piezaActual = bolsa.desencolar();
    eventos.encolarPorTiempo(new EventoVelocidad(30.0f, 0.2f, 15.0f));
    eventos.encolarPorTiempo(new EventoPuntos(85.0f, 25.0f));
    eventos.encolarPorTiempo(new EventoBloque(60.0f));
    eventos.encolarPorTiempo(new EventoVelocidad(110.0f, 0.3f, 20.0f));
    eventos.encolarPorTiempo(new EventoPuntos(145.0f, 30.0f));
    eventos.encolarPorTiempo(new EventoBloque(20.0f));
    registrarEstado();
}

MenuJuego::~MenuJuego() {
    if (fondoSprite != nullptr) delete fondoSprite;
    if (piezaActual != nullptr) delete piezaActual;
}

TipoPantalla MenuJuego::procesarEvento(const Event& evento, const RenderWindow& ventana)
{
    if (gameOver) {
        return TipoPantalla::GameOver;
    }

    if (const auto* keyPressed = evento.getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::A)
        {
            if (comprovarMovimiento(piezaGridX - 1, piezaGridY)) {
                piezaGridX--;
                registrarEstado();
            }
        }
        else if (keyPressed->code == Keyboard::Key::D)
        {
            if (comprovarMovimiento(piezaGridX + 1, piezaGridY)) {
                piezaGridX++;
                registrarEstado();
            }
        }
        else if (keyPressed->code == Keyboard::Key::S)
        {
            if (comprovarMovimiento(piezaGridX, piezaGridY + 1)) {
                piezaGridY++;
                registrarEstado();
            }
            else {
                fijarPieza();
            }
        }
        else if (keyPressed->code == Keyboard::Key::Q)
        {
            if (piezaEspera.estaVacia()) {
                if (piezaActual != nullptr) {
                    piezaActual->resetearOrientacion();
                }
                piezaEspera.apilar(piezaActual);
                piezaActual = bolsa.desencolar();
                piezaGridX = 3;
                piezaGridY = 0;
                registrarEstado();
            }           
        }
        else if (keyPressed->code == Keyboard::Key::E)
        {          
            if (!siguientePiezaEspera && !piezaEspera.estaVacia()) {
                siguientePiezaEspera = true;
                mostrarMensaje("La pieza de espera sera la siguiente en salir.");

            }
        }
        else if (keyPressed->code == Keyboard::Key::Right)
        {
            if (piezaActual != nullptr) {
                piezaActual->rotarDerecha();
                if (!comprovarMovimiento(piezaGridX, piezaGridY)) {
                    piezaActual->rotarIzquierda();
                    
                } else {
                    registrarEstado();
                }                
            }
        }
        else if (keyPressed->code == Keyboard::Key::Left)
        {
            if (piezaActual != nullptr) {
                piezaActual->rotarIzquierda();
                if (!comprovarMovimiento(piezaGridX, piezaGridY)) {
                    piezaActual->rotarDerecha();
                } else {
                    registrarEstado();
                }               
            }
        }
        else if (keyPressed->code == Keyboard::Key::Escape)
        {
            pausa = !pausa;
        }        
    }

    return TipoPantalla::Ninguna;
}

void MenuJuego::actualizar()
{   
    if (gameOver) return;
    if (pausa) {
        mostrarMensaje("Pausa");
        return;
    }

    float dt = relojCaida.restart().asSeconds();

    if (animacionLimpieza) {
        tiempoAnimacionLimpieza -= dt;
        if (tiempoAnimacionLimpieza <= 0.0f) {
            for (int i = 0; i < 20; i++) {
                if (filasAEliminar[i]) {
                    tablero.eliminarEn(i);
                    tablero.insertarInicio(new FilaBloques());
                    puntos += 100 * multiplicadorPuntos;
                    filasAEliminar[i] = false;
                }
            }
            puntaje.setString("Puntaje: " + to_string(puntos));
            animacionLimpieza = false;
            registrarEstado();
        }
        return;
    }

    if (tiempoMensajeEvento > 0.0f) {
        tiempoMensajeEvento -= dt;
    }

    if (duracionPuntosDobles > 0.0f) {
        duracionPuntosDobles -= dt;
        if (duracionPuntosDobles <= 0.0f) {
            duracionPuntosDobles = 0.0f;
            multiplicadorPuntos = 1;
            mostrarMensaje("Puntos Dobles Finalizados!");
        }
    }

    if (duracionVelocidad > 0.0f) {
        duracionVelocidad -= dt;
        if (duracionVelocidad <= 0.0f) {
            duracionVelocidad = 0.0f;
            velocidadCaida = 0.5f;
            mostrarMensaje("Velocidad Normalizada!");
        }
    }

    string infoEventos = "";

    if (duracionVelocidad > 0.0f) {
        int segundos = static_cast<int>(duracionVelocidad) + 1;
        infoEventos += "Vel. Rapida: " + to_string(segundos) + "s\n";
    }

    if (duracionPuntosDobles > 0.0f) {
        int segundos = static_cast<int>(duracionPuntosDobles) + 1;
        infoEventos += "Puntos x2: " + to_string(segundos) + "s\n";
    }

    txtEventosActivos.setString(infoEventos);

    float tiempoActual = relojJuego.getElapsedTime().asSeconds();
    while (!eventos.estaVacia() && eventos.frente()->getTiempo() <= tiempoActual) {
        Evento* ev = eventos.desencolar();
        if (ev != nullptr) {
            ev->ejecutar(*this);
            delete ev;
        }
    }

    tiempoAcumulado += dt;

    if (tiempoAcumulado >= velocidadCaida) {
        if (comprovarMovimiento(piezaGridX, piezaGridY + 1)) {
            piezaGridY++;
            registrarEstado();
        }
        else {
            fijarPieza();
        }
        tiempoAcumulado = 0.0f;
    }

    if (bolsa.estaVacia()) {
        bolsa.rellenarBolsa();
    }
}

void MenuJuego::dibujar(RenderWindow & ventana)
{
    if (fondoSprite != nullptr) {
        ventana.draw(*fondoSprite);
    }

    for (int i = 0; i < tablero.tamano(); i++) {
        FilaBloques* fila = tablero.obtenerEn(i);
        if (fila == nullptr) continue;

        for (int j = 0; j < 10; j++) {
            Bloque* bloqueCelda = fila->columnas[j];
            if (bloqueCelda != nullptr) {
                float px = posXInicial + j * tamanoBloque;
                float py = posYInicial + i * tamanoBloque;

                Sprite* sprite = bloqueCelda->getSprite();
                if (sprite != nullptr) {
                    sprite->setPosition({ px, py });
                    ventana.draw(*sprite);
                }
            }
        }
    }

    if (animacionLimpieza) {
        for (int i = 0; i < 20; i++) {
            if (filasAEliminar[i]) {
                RectangleShape destello({ 10.0f * tamanoBloque, tamanoBloque });
                destello.setPosition({ posXInicial, posYInicial + i * tamanoBloque });
                destello.setFillColor(Color(255, 255, 255, 220));
                ventana.draw(destello);
            }
        }
    }

    if (piezaActual != nullptr) {
        float px = posXInicial + piezaGridX * tamanoBloque;
        float py = posYInicial + piezaGridY * tamanoBloque;
        piezaActual->dibujar(ventana, px, py, tamanoBloque);
    }

    piezaEspera.dibujar(ventana, 150.0f, 150.0f);
    bolsa.dibujar(ventana, 740.0f, 75.0f, tamanoBloque);

    ventana.draw(puntaje);
    ventana.draw(enEspera);
    ventana.draw(siguientePieza);
    ventana.draw(txtEventosActivos);

    if (tiempoMensajeEvento > 0.0f) {
        ventana.draw(textoEvento);
    }
}

void MenuJuego::fijarPieza()
{
    if (!piezaActual) return;

    bool bomba = piezaActual->getDestructor();
    bool filasDestruidasPorBomba[20] = { false };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piezaActual->getCelda(i, j) == 1) {
                int targetY = piezaGridY + i;
                int targetX = piezaGridX + j;

                if (targetY >= 0 && targetY < 20 && targetX >= 0 && targetX < 10) {
                    FilaBloques* fila = tablero.obtenerEn(targetY);
                    if (fila != nullptr) {
                        fila->columnas[targetX] = new Bloque(piezaActual->getForma());
                        filasDestruidasPorBomba[targetY] = true;
                    }
                }
            }
        }
    }

    delete piezaActual;

    if (bomba) {
        bool hayFilas = false;
        for (int y = 0; y < 20; y++) {
            if (filasDestruidasPorBomba[y]) {
                filasAEliminar[y] = true;
                hayFilas = true;
            }
        }
        if (hayFilas) {
            animacionLimpieza = true;
            tiempoAnimacionLimpieza = 0.25f;
        }
        mostrarMensaje("Destruccion masiva!");
    }
    else {
        limpiarFilas();
    }

    if (siguientePiezaEspera) {
        if (!piezaEspera.estaVacia()) {
            piezaActual = piezaEspera.desapilar();
            siguientePiezaEspera = false;
        }
    }
    else {
        piezaActual = bolsa.desencolar();
    }
    if (siguienteDestructor && piezaActual != nullptr) {
        piezaActual->setDestructor(true);
        siguienteDestructor = false;
    }

    piezaGridX = 3;
    piezaGridY = 0;
    registrarEstado();

    if (!comprovarMovimiento(piezaGridX, piezaGridY)) {
        gameOver = true;
        gestorPuntajes.agregarPuntaje(nombreJugador, puntos);
    }
}

void MenuJuego::limpiarFilas()
{
    bool filasCompletas = false;
    for (int i = 0; i < tablero.tamano(); i++) {
        FilaBloques* fila = tablero.obtenerEn(i);
        if (fila && fila->filaLlena()) {
            filasAEliminar[i] = true;
            filasCompletas = true;
        }
    }

    if (filasCompletas) {
        animacionLimpieza = true;
        tiempoAnimacionLimpieza = 0.25f;
    }
}

bool MenuJuego::comprovarMovimiento(int nuevoX, int nuevoY)
{
    if (!piezaActual) return false;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (piezaActual->getCelda(i, j) == 1) {
                int targetX = nuevoX + j;
                int targetY = nuevoY + i;

                if (targetX < 0 || targetX >= 10 || targetY >= 20) {
                    return false;
                }

                if (targetY >= 0) {
                    FilaBloques* fila = tablero.obtenerEn(targetY);
                    if (fila != nullptr && fila->columnas[targetX] != nullptr) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void MenuJuego::mostrarMensaje(const string& mensaje)
{
    textoEvento.setString(mensaje);
    tiempoMensajeEvento = 3.0f;
}

void MenuJuego::activarVelocidadAumentada(float nuevaVelocidad, float duracion)
{
    velocidadCaida = nuevaVelocidad;
    duracionVelocidad = duracion;
    mostrarMensaje("¡Velocidad Aumentada!");
}

void MenuJuego::destruirFilaCompleta(int filaIndex)
{
    if (filaIndex >= 0 && filaIndex < tablero.tamano()) {
        tablero.eliminarEn(filaIndex);
        tablero.insertarInicio(new FilaBloques());
        puntos += 100 * multiplicadorPuntos;
        puntaje.setString("Puntaje: " + to_string(puntos));
        mostrarMensaje("Fila Destruida!");
        registrarEstado();
    }
}

void MenuJuego::registrarEstado()
{
    EstadoJuego estado;
    estado.puntos = puntos;
    estado.piezaGridX = piezaGridX;
    estado.piezaGridY = piezaGridY;

    if (piezaActual != nullptr) {
        estado.piezaActualForma = piezaActual->getForma();
        estado.piezaActualRotacion = piezaActual->getOrientacion();
    }

    if (!piezaEspera.estaVacia()) {
        estado.piezaEsperaForma = piezaEspera.tope()->getForma();
        estado.tienePiezaEspera = true;
    }
    else {
        estado.tienePiezaEspera = false;
    }

    estado.cantidadBolsa = bolsa.tamano();
    for (int i = 0; i < bolsa.tamano() && i < 10; i++) {
        Bloque* pieza = bolsa.verEn(i);
        if (pieza != nullptr) {
            estado.bolsa[i] = pieza->getForma();
        }
    }

    for (int i = 0; i < 20; i++) {
        FilaBloques* fila = tablero.obtenerEn(i);
        for (int j = 0; j < 10; j++) {
            if (fila != nullptr && fila->columnas[j] != nullptr) {
                estado.matrizTablero[i][j] = fila->columnas[j]->getForma();
                estado.matrizOcupada[i][j] = true;
            }
            else {
                estado.matrizOcupada[i][j] = false;
            }
        }
    }

    replay.insertarFinal(estado);
}