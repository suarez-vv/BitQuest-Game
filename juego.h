#ifndef JUEGO_H
#define JUEGO_H

#include "mapas.h"
#include <stdbool.h>

//Inicialización del juego
void iniciarJuego();

//Lógica de como va avanzando el juego
void estadoJuego();

//Llamar la parte gráfica de raylib
void llamarDibujar();

//Limpiar al finalizar
void limpiar();

//Identificar en que nivel del juego se encuentra el jugador
void cambiarNivel(int);

//Función en ensamblador
int contarAcumulables(char*, int, int);

//Veirificar si se puede abrir una puerta en el mapa
bool abrirPuerta(int);

//Actualizar caracteres de mapa
void actualizarMapa(char*, int, int);

#endif