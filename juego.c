#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "graficos.h"
#include "mapas.h"

#define VIEW 20

int camX = 0;
int camY = 0;
int jugadorX = 1;
int jugadorY = 1;
int nivel = 0;
int mapSize = 0;
int celdasLibres = 0;
bool iniciandoNivel = true;
bool actualiMapa = false;
char *mapActual = NULL;
int totalMonedas = 0; //Cantidad total de monedas en todos los niveles
int totalLlaves = 0; //Cantidad total de llaves en todos los niveles
int monedas_Nivel = 0; //Cantidad de monedas que hay en un nivel
int llaves_Nivel = 0; //Cantidad de llaves que hay en un nivel
int monedasObtNivel = 0; //Monedas obtenidas en un nivel
int llavesObtNivel = 0; //Llaves obtenidas en un nivel
int llavesUtilNivel = 0; //Contador de las llaves que se uitilizan en un nivel (incrementa y drecrementa)
int pasosNivel = 0; //Pasos realizados durante un nivel
int monedasAcum = 0; //Monedas acumuladas durante todo el juego
int llavesAcum = 0; //Llaves acumuladas durante todo el juego
int pasosAcum = 0; //Pasos realizados durante todo el juego
int nivelesComp = 0; //Cantidad de niveles completados
int puntajeFinal = 0; //Puntaje final del juego
int estado = 1; //1=Jugando un nivel, 2=Pasando de nivel, 3=Fin del juego

void iniciarJuego(){
    cambiarNivel();
    iniciarGraficos();
}

void estadoJuego(){
    //Si acabamos el nivel se ve la pantalla de fin de este, cambiamos de nivel
    if(estado == 2){
        if(IsKeyPressed(KEY_ENTER)){

            if(nivelesComp == 3){ //Ya se completaron los 3 niveles entonces es el fin del juego
                estado = 3;
            }else{
                estado = 1;
                cambiarNivel();
            }
        }
        return;
    }

    if(iniciandoNivel){
        celdasLibres = contarCeldasLibres(mapActual, (mapSize*mapSize));
        monedas_Nivel = contarCaracter(mapActual, (mapSize*mapSize), 'M');
        llaves_Nivel = contarCaracter(mapActual, (mapSize*mapSize), 'K');
        iniciandoNivel = false;
    }

    int destinoX = jugadorX;
    int destinoY = jugadorY;

    //Movimiento con wasd y salida con q
    if(IsKeyPressed(KEY_W)) destinoY--; //Hacia arriba
    if(IsKeyPressed(KEY_A)) destinoX--; //Izquierda
    if(IsKeyPressed(KEY_S)) destinoY++; //Abajo
    if(IsKeyPressed(KEY_D)) destinoX++; //Derecha
    if(IsKeyPressed(KEY_Q)){ //Salir del juego
        estado = 3;
        return;
    }

    //Comprobar que la casilla propuesta este dentro del mapa
    if(destinoX >=0 && destinoX <mapSize && destinoY >= 0 && destinoY < mapSize){
        //Validar el movimiento del jugador
        if(validarMovimiento(mapActual, mapSize, destinoY, destinoX)){ //Si no es una pared revisamos qué es
            actualiMapa = true;
            if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, 'M')){ //Si es una moneda
                monedasObtNivel++;
            }else if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, 'K')){ //Si es una llave
                llavesObtNivel++;
                llavesUtilNivel++;
            }else if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, 'D')){ //Si es una puerta
                if(llavesUtilNivel < 1) actualiMapa = false; //Si no tiene una llave para abrir la puerta entonces no habra movimiento y el mapa no se actualizará
                else llavesUtilNivel--; //Si tiene una llave para abrir la puerta entonces se consume la llave y se actualiza el mapa con el movimiento
            }else if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, 'E')){ //Si es una salida
                nivelesComp++;
                totalMonedas += monedas_Nivel;
                totalLlaves += llaves_Nivel;
                monedasAcum += monedasObtNivel;
                llavesAcum += llavesObtNivel;
                pasosAcum += pasosNivel;

                estado = 2;
                return;
            }else if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, '.')){ // Si es piso
                //El mapa se actualiza y los pasos se aumentan abajo al actualizar el mapa
            }else{
                TraceLog(LOG_WARNING, "Casilla desconocida, informar de revisión para el mapa");
            }
        }else{ //Si hay una pared no se puede mover hacia porque no se puede atravesar paredes, el mapa no se actualiza
            actualiMapa = false;
        }

        //Sí se realizo un movimiento valido y hay que actualizar el mapa, sino no se movera y no hay que atcualizar mapa
        if(actualiMapa && (jugadorY != destinoY || jugadorX != destinoX)){
            actualizarMapa(mapActual, mapSize, jugadorY, jugadorX, destinoY, destinoX);

            pasosNivel++;
            jugadorX = destinoX;
            jugadorY = destinoY;
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
}

void llamarDibujar(bool *status){
    BeginDrawing();
    ClearBackground((Color){55.6f, 51.3f, 47.4f, 255.0f});

    if(estado == 1){
        DrawRectangle(0, 0, 640, 80, BLACK);
        DrawLine(0, 80, 640, 80, BLACK);
        dibujar_mapa(mapActual, camX, camY, mapSize);
        dibujarJugador(jugadorX, jugadorY, camX, camY);

        DrawText(TextFormat("Nivel: %d", nivel), 80, 10, 22, WHITE);
        DrawText(TextFormat("Monedas: %d", monedasObtNivel), 180, 10, 22, GOLD);
        DrawText(TextFormat("Llaves: %d", llavesUtilNivel), 340, 10, 22, WHITE);
        DrawText(TextFormat("Pasos: %d", pasosNivel), 470, 10, 22, WHITE);
        DrawText("W: Arriba, S: Abajo, A: Izquierda, D: Derecha, Q: Salir", 120, 45, 17, LIGHTGRAY);
    }else if(estado == 2){
        ClearBackground(BLACK);
        DrawText("FELICIDADES!!!", 200, 150, 40, YELLOW);
        DrawText(TextFormat("NIVEL %d COMPLETADO", nivel), 120, 220, 20, WHITE);
        DrawText(TextFormat("MONEDAS: %d/%d", monedasObtNivel, monedas_Nivel), 140, 280, 20, WHITE);
        DrawText(TextFormat("LLAVES: %d/%d", llavesObtNivel, llaves_Nivel), 140, 320, 20, WHITE);
        DrawText(TextFormat("PASOS: %d", pasosNivel), 140, 360, 20, WHITE);
         DrawText(TextFormat("CASILLAS DISPONIBLES PARA MOVERSE: %d", celdasLibres), 140, 400, 20, WHITE);
        if(nivel < 3){
            DrawText("Presiona 'ENTER' para ir al siguiente nivel", 120, 480, 20, WHITE);
        }else {
            DrawText("Presiona 'ENTER' para ver tu puntaje final", 120, 440, 20, WHITE);
        }
    }else if(estado == 3){
        static bool continuar = false;
        ClearBackground(BLACK);
        puntajeFinal = calcularPuntaje(monedasAcum, llavesAcum, pasosAcum, nivelesComp);
        DrawText("GAME OVER", 200, 120, 40, YELLOW);
        DrawText("GRACIAS POR JUGAR", 100, 400, 40, GOLD);
        DrawText(TextFormat("Monedas totales recolectadas: %d/%d", monedasAcum, totalMonedas), 50, 200, 30, WHITE);
        DrawText(TextFormat("Pasos totales: %d", pasosAcum), 190, 240, 30, WHITE);
        DrawText(TextFormat("Niveles completados: %d", nivelesComp), 150, 280, 30, WHITE);
        DrawText(TextFormat("Puntaje final: %d", puntajeFinal), 190, 320, 30, WHITE);
        DrawText(TextFormat("Presiona 'Enter' para salir..."), 170, 450, 20, DARKGRAY);
        if(IsKeyReleased(KEY_ENTER)){
            continuar = true;
        }
        if(continuar && IsKeyPressed(KEY_ENTER)){
            *status = false;
        }
    }
    EndDrawing();
}

void limpiar(){
    finGraficos();
}

void cambiarNivel(){
    iniciandoNivel = true;
    camX = 0;
    camY=0;
    jugadorX=1;
    jugadorY=1;
    monedasObtNivel = 0;
    pasosNivel = 0;
    llavesObtNivel = 0;

    if(nivel == 3){ //Al acabar el nivel 3 se acaba el juego
        return;
    }

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
//Contar un caracter especifico del mapa (Funcion obligatoria 1)
int contarCaracter(char *mapa, int mapSize, char buscado);

//Contar un caracter especifico del mapa (Funcion obligatoria 2)
int validarMovimiento(char *mapa, int mapSize, int newColumna, int newFila); //(Se puede usar en lugar de actualizarMapa)

//Calcular puntaje al finalizar nivel (Funcion olbigatoria 3)
int calcularPuntaje(int totalMonedasAcum, int llavesAcum, int cantPasos, int nivelComp);

//Detectar si hay cierto objeto en el mapa (Funcion olbigatoria 4)
int detectarObjeto(char *mapa, int mapSize, int columnaRev, int filaRev, char buscado); //contarAcumulables (Se puede usar en lugar de abrirPuerta)

//Contar un caracter especifico del mapa (Funcion obligatoria 5)
int contarCeldasLibres(char *mapa, int mapSize); //contarCeldasDisp

//Actualizar el mapa luego de un movimiento
void actualizarMapa(char *mapa, int mapSize, int columnaActual, int filaActual, int columnaMov, int filaMov);