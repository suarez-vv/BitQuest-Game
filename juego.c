#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "graficos.h"

int camX = 0;
int camY=0;

int jugadorX=2;
int jugadorY=2;
int nivel = 0;
int mapSize = 0;
char *mapActual = NULL;
int monedasAcum = 0;
int llavesAcum = 0;

void iniciarJuego(){
    cambiarNivel(nivel);
    iniciarGraficos();
}

void estadoJuego(){

    int actualX = jugadorX;
    int actualY = jugadorY;

    //Movimiento con wasd
    if(IsKeyDown(KEY_W)) actualY--; //Hacia arriba
    if(IsKeyDown(KEY_A)) actualX--; //Izquierda
    if(IsKeyDown(KEY_S)) actualY++; //Abajo
    if(IsKeyDown(KEY_D)) actualX++; //Derecha

    //Comprobar que este dentro del mapa
    if(actualX >=0 && actualX <mapSize && actualY >= 0 && actualY < mapSize){
        int posMapa = actualY * mapSize + actualX;

        int auxCasilla;

        //Logica para las casillas y lo que haya en ellas
        auxCasilla = contarAcumulables(mapActual, mapSize, posMapa);
        
        switch(auxCasilla){
            case 0: monedasAcum++;
                break;
            case 1: llavesAcum++;
                break;
            case 2: 
                    bool abrir = abrirPuerta(llavesAcum);
                    if(abrir){
                        llavesAcum--;
                    }else{
                        auxCasilla = 4;
                    }
                break;
            case 3: //Logica para la salida
                break;
        };

        //Un 4 significa una pared en tal caso no se movera y no hay que atcualizar mapa
        if(auxCasilla != 4){
            jugadorX = actualX;
            jugadorY = actualY;

            actualizarMapa(mapActual, mapSize, posMapa);
        }
        /*Hay que revisar si es una pared que no se atraviese esta,
        si es una moneda recogerla y actualizar el mapa,
        si es una llave recogerla y actualizar el mapa,
        si es camino realizar el movimiento,
        si es la salida mostrar pantalla de fin del nivel*/
    }

    //Actualizar camara
    camX = jugadorX - (20/2);
    camY = jugadorY - (20/2);

    //El limite de la camara
    if(camX < 0) camX = 0;
    if(camY < 0) camY = 0;

    if(camX > mapSize - 20) camX = mapSize - 20;
    if(camY > mapSize - 20) camY = mapSize - 20;

}

void llamarDibujar(){
    BeginDrawing();
    ClearBackground(BLACK);

    dibujar_mapa(mapActual, camX, camY, mapSize);
    dibujarJugador(jugadorX, jugadorY, camX, camY);

    DrawText(TextFormat("Nivel: %d", nivel), 10, 10, 20, WHITE);
    DrawText(TextFormat("Monedas: %d", monedasAcum), 10, 30, 20, GOLD);
    DrawText(TextFormat("Llaves: %d", llavesAcum), 10, 50, 20, WHITE);

    EndDrawing();
}

void limpiar(){
    finGraficos();
}

void cambiarNivel(int nivel){
    nivel++;
    if(nivel == 1){
        mapActual = &mapa1[0][0];
        mapSize = MAP1_SIZE;
        return;
    }else if(nivel == 2){
        mapActual = &mapa2[0][0];
        mapSize = MAP2_SIZE;
        return;
    }else if(nivel == 3){
        mapActual = &mapa3[0][0];
        mapSize = MAP3_SIZE;
        return;
    }else{
        //Error en el nivel y mapa
        TraceLog(LOG_WARNING, "Error en el número de nivel");
        return;
    }
}

//Funciones de ensamblador
int contarAcumulables(char *mapa, int totalCeldas, int posMapa);

bool abrirPuerta(int numLlaves);

void actualizarMapa(char *mapa, int totalCeldas, int posMapa);