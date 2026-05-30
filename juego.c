#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "graficos.h"
#include "mapas.h"

#define VIEW 20

int camX = 0;
int camY = 0;
int jugadorX = 2;
int jugadorY = 2;
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
int nivelesComp = -1; //Cantidad de niveles completados
int puntajeFinal = 0; //Puntaje final del juego
int estado = 1; //1=Jugando un nivel, 2=Pasando de nivel, 3=Final del juego

void iniciarJuego(){
    cambiarNivel();
    iniciarGraficos();
}

void estadoJuego(){
    //Si acabamos el nivel se ve la pantalla de fin de este, cambiamos de nivel
    if(estado == 2){
        if(IsKeyPressed(KEY_ENTER)){
            if(nivelesComp == 3){ //Agregar que si se presiona 'Q' tambien se acabe el juego
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
    if(IsKeyPressed(KEY_Q)){
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
                if(llavesObtNivel < 1) actualiMapa = false; //Si no tiene una llave para abrir la puerta entonces no habra movimiento y el mapa no se actualizará
                else llavesUtilNivel--; //Si tiene una llave para abrir la puerta entonces se consume la llave y se actualiza el mapa con el movimiento
            }else if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, 'E')){ //Si es una salida
                estado = 2;
                return;
            }else if(detectarObjeto(mapActual, mapSize, destinoY, destinoX, '.')){ // Si es piso
                pasosNivel++;
            }else{
                TraceLog(LOG_WARNING, "Casilla desconocida, informar de revisión para el mapa");
            }
        }else{ //Si hay una pared no se puede mover hacia porque no se puede atravesar paredes, el mapa no se actualiza
            actualiMapa = false;
        }

        //Sí se realizo un movimiento valido y hay que actualizar el mapa, sino no se movera y no hay que atcualizar mapa
        if(actualiMapa){
            actualizarMapa(mapActual, mapSize, jugadorY, jugadorX, destinoY, destinoX);

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

void llamarDibujar(){
    BeginDrawing();
    ClearBackground((Color){55.6f, 51.3f, 47.4f, 255.0f});

    if(estado == 1){
        dibujar_mapa(mapActual, camX, camY, mapSize);
        dibujarJugador(jugadorX, jugadorY, camX, camY);

        DrawText(TextFormat("Nivel: %d", nivel), 10, 10, 20, WHITE);
        DrawText(TextFormat("Monedas: %d", monedasObtNivel), 10, 30, 20, GOLD);
        DrawText(TextFormat("Llaves: %d", llavesUtilNivel), 10, 50, 20, WHITE);
    }else if(estado == 2){
        DrawText("FELICIDADES!!!", 200, 150, 40, YELLOW);
        DrawText(TextFormat("NIVEL %d COMPLETADO", nivel), 120, 220, 20, WHITE);
        
        switch(nivel){
            case 1:
                DrawText(TextFormat("MONEDAS: %d/%d", monedasObtNivel, monedas_Nivel), 200, 280, 20, WHITE);
                DrawText(TextFormat("LLAVES: %d/%d", llavesObtNivel, llaves_Nivel), 200, 320, 20, WHITE);
                DrawText("Presiona ENTER para ir al siguiente nivel", 120, 400, 20, WHITE);
                break;
            case 2:
                DrawText(TextFormat("MONEDAS: %d/%d", monedasObtNivel, monedas_Nivel), 200, 280, 20, WHITE);
                DrawText(TextFormat("LLAVES: %d/%d", llavesObtNivel, llaves_Nivel), 200, 320, 20, WHITE);
                DrawText("Presiona ENTER para ir al siguiente nivel", 120, 400, 20, WHITE);
                break;
            case 3: //Aqui agregar logica para terminarel juego
                DrawText(TextFormat("MONEDAS: %d/%d", monedasObtNivel, monedas_Nivel), 200, 280, 20, WHITE);
                DrawText(TextFormat("LLAVES: %d/%d", llavesObtNivel, llaves_Nivel), 200, 320, 20, WHITE);
                break;
            default: TraceLog(LOG_WARNING, "Error en el número de nivel");
                break;
        }
    }else if(estado == 3){
        puntajeFinal = calcularPuntaje(monedasAcum, pasosAcum, nivelesComp);
        DrawText("GAME OVER", 150, 280, 40, YELLOW);
        DrawText("GRACIAS POR JUGAR", 80, 260, 40, GOLD);
        DrawText(TextFormat("Monedas totales recolectadas: %d/%d", monedasAcum, totalMonedas), 200, 240, 30, WHITE);
        DrawText(TextFormat("Pasos totales: %d", pasosAcum), 200, 220, 30, WHITE);
        DrawText(TextFormat("Niveles completados: %d", nivelesComp), 200, 200, 30, WHITE);
        DrawText(TextFormat("Puntaje final: %d", puntajeFinal), 200, 180, 30, WHITE);
    }
    

    
    EndDrawing();
}

void limpiar(){
    finGraficos();
}

void cambiarNivel(){
    //Iniciar-reiniciar variables del juego
    nivelesComp++;
    totalMonedas += monedas_Nivel;
    totalLlaves += llaves_Nivel;
    monedasAcum += monedasObtNivel;
    llavesAcum += llavesObtNivel;
    pasosAcum += pasosNivel;
    iniciandoNivel = true;
    camX = 0;
    camY=0;
    jugadorX=2;
    jugadorY=2;
    monedasObtNivel = 0;
    pasosNivel = 0;
    llavesObtNivel = 0;

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
int calcularPuntaje(int totalMonedasAcum, int cantPasos, int nivelComp);

//Detectar si hay cierto objeto en el mapa (Funcion olbigatoria 4)
int detectarObjeto(char *mapa, int mapSize, int columnaRev, int filaRev, char buscado); //contarAcumulables (Se puede usar en lugar de abrirPuerta)

//Contar un caracter especifico del mapa (Funcion obligatoria 5)
int contarCeldasLibres(char *mapa, int mapSize); //contarCeldasDisp

//Actualizar el mapa luego de un movimiento
void actualizarMapa(char *mapa, int mapSize, int columnaActual, int filaActual, int columnaMov, int filaMov);