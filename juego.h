#ifndef JUEGO_H
#define JUEGO_H
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
void cambiarNivel();

//Contar un caracter especifico del mapa (Funcion obligatoria 1)
int contarCaracter(char*, int, char);

//Contar un caracter especifico del mapa (Funcion obligatoria 2)
int validarMovimiento(char*, int, int, int); //(Se puede usar en lugar de actualizarMapa)

//Calcular puntaje al finalizar el juego (Funcion olbigatoria 3)
int calcularPuntaje(int, int, int);

//Detectar si hay cierto objeto en el mapa (Funcion olbigatoria 4)
int detectarObjeto(char*, int, int, int, char); //contarAcumulables (Se puede usar en lugar de abrirPuerta)

//Contar un caracter especifico del mapa (Funcion obligatoria 5)
int contarCeldasLibres(char*, int); //contarCeldasDisp

//Actualizar caracteres de mapa
void actualizarMapa(char*, int, int, int, int, int);

#endif
