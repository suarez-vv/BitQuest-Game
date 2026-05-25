#ifndef GRAFICOS_H
#define GRAFICOS_h

#include "raylib.h"

//Inicializacion de la parte grafica de raylib
void inicioGraficos();

//Mapa
void dibujar_mapa(char *mapActual, int camX, int camY, int mapSize);

//Jugador
void dibujarJugador(int jugadorX, int jugadorY, int camX, int camY);

//Cerrar y limpiar al finalizar el programa
void finGraficos();

#endif