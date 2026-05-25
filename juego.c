#include "juego.h"
#include "graficos.h"

int camX = 0;
int camY=0;

int jugadorX=2;
int jugadorY=2;
int nivel;
int mapSize;
char *mapActual;

void nivel(){
    if(nivel == 1){
        mapActual = &mapa1[0][0];
        mapSize = MAP1_SIZE;
    }else if(nivel == 2){
        mapActual = &mapa2[0][0];
        mapSize = MAP2_SIZE;
    }else if(nivel == 3){
        mapActual = &mapa3[0][0];
        mapSize = MAP3_SIZE;
    }else{
        //Error en el nivel y mapa
    }
}