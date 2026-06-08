#ifndef GRAFICOS_H
#define GRAFICOS_h

#include "raylib.h"

//Inicializacion de la parte grafica de raylib
void iniciarGraficos();

//Dibujar el mapa
void dibujar_mapa(char *mapActual, int camX, int camY, int mapSize);

//Dibujar el jugador
void dibujarJugador(int jugadorX, int jugadorY, int camX, int camY);

//Actualizar la música del fondo del juego
void actualizarMusica();

//Cerrar y limpiar al finalizar el programa
void finGraficos();

#endif