#ifndef JUEGO_H
#define JUEGO_H
#include <stdbool.h>

//Inicialización del juego
void iniciarJuego();

//Lógica de como va avanzando el juego
void estadoJuego();

//Llamar la parte gráfica de raylib
void llamarDibujar(bool *status);

//Limpiar al finalizar
void limpiar();

//Identificar en que nivel del juego se encuentra el jugador
void cambiarNivel();

//Cargar un mapa desde un archivo de texto externo
char *cargarMapa(const char *nombreArchivo, int mapSize);

// 1 Contar un caracter especifico del map
int contarCaracter(char*, int, char);

// 2 Contar un caracter especifico del mapa
int validarMovimiento(char*, int, int, int);

// 3 Calcular puntaje al finalizar el juego
int calcularPuntaje(int, int, int, int);

// 4 Detectar si hay cierto objeto en el mapa
int detectarObjeto(char*, int, int, int, char);

// 5 Contar un caracter especifico del mapa 
int contarCeldasLibres(char*, int);

//Actualizar caracteres de mapa
void actualizarMapa(char*, int, int, int, int, int);

#endif