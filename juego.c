#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "graficos.h"

#define VIEW 20

int camX = 0;
int camY = 0;
int jugadorX = 2;
int jugadorY = 2;
int nivel = 0;
int mapSize = 0;
char *mapActual = NULL;
int monedasAcum = 0;
int llavesAcum = 0;
int estado = 1; //1=Jugando un nivel, 2=Pasando de nivel, 3=Final del juego

void iniciarJuego(){
    cambiarNivel();
    iniciarGraficos();
}

void estadoJuego(){
    //Si acabamos el nivel esta la pantalla de fin de este, cambiamos de nivel
    if(estado == 2){
        if(IsKeyPressed(KEY_ENTER)){
            if(nivel == 3){
                estado = 3;
            }else{
                estado = 1;
                cambiarNivel();
            }
        }
        return;
    }

    int actualX = jugadorX;
    int actualY = jugadorY;
    int auxCasilla;

    //Movimiento con wasd
    if(IsKeyDown(KEY_W)) actualY--; //Hacia arriba
    if(IsKeyDown(KEY_A)) actualX--; //Izquierda
    if(IsKeyDown(KEY_S)) actualY++; //Abajo
    if(IsKeyDown(KEY_D)) actualX++; //Derecha

    //Comprobar que este dentro del mapa
    if(actualX >=0 && actualX <mapSize && actualY >= 0 && actualY < mapSize){
        int posSigMapa = actualY * mapSize + actualX;
        int posActualMapa = jugadorY * mapSize + jugadorX;

        //Logica para las casillas y lo que haya en ellas
        auxCasilla = contarAcumulables(mapActual, posSigMapa);
        
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
            default: TraceLog(LOG_WARNING, "Casilla desconocida, revisar el mapa");
                break;
        };

        //Un 4 significa una pared o una puerta que no se puede abrir, en tal caso no se movera y no hay que atcualizar mapa
        if(auxCasilla != 4){
            actualizarMapa(mapActual, posActualMapa, posSigMapa);

            jugadorX = actualX;
            jugadorY = actualY;
        }
    }

    //Actualizar camara
    camX = jugadorX - (VIEW/2);
    camY = jugadorY - (VIEW/2);

    //El limite de la camara
    if(camX < 0) camX = 0;
    if(camY < 0) camY = 0;

    if(camX > mapSize - VIEW) camX = mapSize - VIEW;
    if(camY > mapSize - VIEW) camY = mapSize - VIEW;

    if(auxCasilla == 3){
        estado = 2;
        return;
    }

}

void llamarDibujar(){
    BeginDrawing();
    ClearBackground(BLACK);

    if(estado == 1){
        dibujar_mapa(mapActual, camX, camY, mapSize);
        dibujarJugador(jugadorX, jugadorY, camX, camY);

        DrawText(TextFormat("Nivel: %d", nivel), 10, 10, 20, WHITE);
        DrawText(TextFormat("Monedas: %d", monedasAcum), 10, 30, 20, GOLD);
        DrawText(TextFormat("Llaves: %d", llavesAcum), 10, 50, 20, WHITE);
    }else if(estado == 2){
        DrawText("FELICIDADES!!!", 200, 150, 40, YELLOW);
        DrawText(TextFormat("NIVEL %d COMPLETADO", nivel), 120, 220, 20, WHITE);
        
        switch(nivel){
            case 1:
                DrawText(TextFormat("MONEDAS: %d/%d", monedasAcum, MAP1_MONEDAS), 200, 280, 20, WHITE);
                DrawText(TextFormat("LLAVES: %d/%d", llavesAcum, MAP1_LLAVES), 200, 320, 20, WHITE);
                DrawText("Presiona ENTER para ir al siguiente nivel", 120, 400, 20, WHITE);
                break;
            case 2:
                DrawText(TextFormat("MONEDAS: %d/%d", monedasAcum, MAP2_MONEDAS), 200, 280, 20, WHITE);
                DrawText(TextFormat("LLAVES: %d/%d", llavesAcum, MAP2_LLAVES), 200, 320, 20, WHITE);
                DrawText("Presiona ENTER para ir al siguiente nivel", 120, 400, 20, WHITE);
                break;
            case 3: //Aqui agregar logica para terminarel juego
                DrawText(TextFormat("MONEDAS: %d/%d", monedasAcum, MAP3_MONEDAS), 200, 280, 20, WHITE);
                DrawText(TextFormat("LLAVES: %d/%d", llavesAcum, MAP3_LLAVES), 200, 320, 20, WHITE);
                break;
            default: TraceLog(LOG_WARNING, "Error en el número de nivel");
                break;
        }
    }else if(estado == 3){
        DrawText("HAS COMPLETADO TODOS LOS NIVELES!!!", 150, 200, 40, WHITE);
        DrawText("GRACIAS POR JUGAR", 80, 260, 40, GOLD);
    }
    

    
    EndDrawing();
}

void limpiar(){
    finGraficos();
}

void cambiarNivel(){
    //Iniciar-reiniciar variables del juego
    camX = 0;
    camY=0;
    jugadorX=2;
    jugadorY=2;
    monedasAcum = 0;
    llavesAcum = 0;

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
int contarAcumulables(char *mapa, int posSigMapa);

bool abrirPuerta(int numLlaves);

void actualizarMapa(char *mapa, int posActualMapa, int posSigMapa);

int calcularPuntaje(int monedas, int llaves, int pasos);

int contarCeldasDisp(char *mapa, int totalCeldas);
