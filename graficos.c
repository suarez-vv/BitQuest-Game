#include "graficos.h"

#define VIEW_SIZE 20
#define TILE 32

Texture2D pared;
Texture2D piso;
Texture2D puerta;
Texture2D moneda;
Texture2D jugador;
Texture2D salida;

//Inicializacion de la parte grafica de raylib
void inicioGraficos(){
    InitWindow(VIEW_SIZE * TILE, VIEW_SIZE * TILE, "BitQuest");
    SetTargetFPS(60);

    
}

//Mapa
void dibujar_mapa(char *mapActual, int camX, int camY, int mapSize){

}

//Jugador
void dibujarJugador(int jugadorX, int jugadorY, int camX, int camY){

}

//Cerrar y limpiar al finalizar el programa
void finGraficos(){
    //Quitar todas las texturas cargadas
    CloseWindow();
}