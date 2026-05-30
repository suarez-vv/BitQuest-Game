#include "graficos.h"

#define VIEW_SIZE 20 //Vista de solo 20x20
#define TILE 32 //Tamaño de casilla en pixeles

Texture2D pared;
Texture2D camino;
Texture2D puerta;
Texture2D moneda;
Texture2D jugador;
Texture2D salida;
Texture2D llave;

//Inicializacion de la parte grafica de raylib
void iniciarGraficos(){
    InitWindow(VIEW_SIZE * TILE, VIEW_SIZE * TILE, "BitQuest");
    SetTargetFPS(60);

    //Poner las imagenes de las texturas de cada objet
    pared = LoadTexture("Pared.png");
    camino = LoadTexture("Piso.png");
    puerta = LoadTexture("Puerta.png");
    moneda = LoadTexture("Moneda.png");
    jugador = LoadTexture("Jugador.png");
    salida = LoadTexture("Salida.png");
    llave = LoadTexture("LLave.png");

    //Suavizar las orillas de las texturas
    SetTextureFilter(pared, TEXTURE_FILTER_POINT);
    SetTextureFilter(camino, TEXTURE_FILTER_POINT);
    SetTextureFilter(puerta, TEXTURE_FILTER_POINT);
    SetTextureFilter(moneda, TEXTURE_FILTER_POINT);
    SetTextureFilter(jugador, TEXTURE_FILTER_POINT);
    SetTextureFilter(salida, TEXTURE_FILTER_POINT);
    SetTextureFilter(llave, TEXTURE_FILTER_POINT);

    SetTextureWrap(pared, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(camino, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(puerta, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(moneda, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(jugador, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(salida, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(llave, TEXTURE_WRAP_CLAMP);

    //Comprobar que las imagenes si se carguen correctamente
    if(pared.id == 0) TraceLog(LOG_WARNING, "Textura de 'Pared' no se cargo correctamente");
    if(camino.id == 0) TraceLog(LOG_WARNING, "Textura de 'Camino' no se cargo correctamente");
    if(moneda.id == 0) TraceLog(LOG_WARNING, "Textura de 'Moneda' no se cargo correctamente");
    if(puerta.id == 0) TraceLog(LOG_WARNING, "Textura de 'Puerta' no se cargo correctamente");
    if(jugador.id == 0) TraceLog(LOG_WARNING, "Textura de 'Jugador' no se cargo correctamente");
    if(salida.id == 0) TraceLog(LOG_WARNING, "Textura de 'Salida' no se cargo correctamente");
    if(llave.id == 0) TraceLog(LOG_WARNING, "Textura de 'Llave' no se cargo correctamente");
}

//Mapa
void dibujar_mapa(char *mapActual, int camX, int camY, int mapSize){
    for(int i=0; i<VIEW_SIZE; i++){
        for(int j=0; j<VIEW_SIZE; j++){

            int mapX = camX + j;
            int mapY = camY + i;

            int indice = mapY * mapSize + mapX;

            /*
                # = Pared
                . = Camino
                P = Jugador
                M = Moneda
                K = Llave
                D = Puerta
                E = Salida
            */

            //Cambiar los caracteres por las texturas
            switch(mapActual[indice]){
                case '#':
                    DrawTexturePro(pared, 
                        (Rectangle){500.0f, 500.0f, (float)pared.width - 1000.0f,
                        (float)pared.height - 1000.0f}, //Imagen completa
                        (Rectangle){(float)(j*TILE), (float)(i*TILE), (float)(TILE+1), (float)(TILE+1)}, //Imagen escalada
                        (Vector2){0,0},
                        0.0f,
                        WHITE
                    );
                    break;
                case '.':
                    DrawTexturePro(camino, 
                        (Rectangle){500.0f, 500.0f, (float)camino.width - 1000.0f,
                        (float)camino.height-1000.0f}, //Origen (imagen completa)
                        (Rectangle){(float)(j*TILE), (float)(i*TILE), (float)(TILE+1), (float)(TILE+1)}, //destino escalado
                        (Vector2){0,0},
                        0.0f,
                        WHITE
                    );
                    break;
                case 'M':
                    DrawTexturePro(moneda, 
                        (Rectangle){25.0f, 40.0f, (float)moneda.width - 50.0f,
                        (float)moneda.height - 80.0f}, //Origen (imagen completa)
                        (Rectangle){(float)(j*TILE), (float)(i*TILE), (float)(TILE+1), (float)(TILE+1)}, //destino escalado
                        (Vector2){0,0},
                        0.0f,
                        WHITE
                    );
                    break;
                case 'K':
                    DrawTexturePro(llave, 
                        (Rectangle){2.0f, 6.0f, (float)llave.width - 4.0f,
                        (float)llave.height - 12.0f}, //Origen (imagen completa)
                        (Rectangle){(float)(j*TILE), (float)(i*TILE), (float)(TILE+1), (float)(TILE+1)}, //destino escalado
                        (Vector2){0,0},
                        0.0f,
                        WHITE
                    );
                    break;
                case 'D':
                    DrawTexturePro(puerta, 
                        (Rectangle){390.0f, 50.0f, (float)puerta.width - 780.0f,
                        (float)puerta.height - 100.0f}, //Origen (imagen completa)
                        (Rectangle){(float)(j*TILE), (float)(i*TILE), (float)(TILE+1), (float)(TILE+1)}, //destino escalado
                        (Vector2){0,0},
                        0.0f,
                        WHITE
                    );
                    break;
                case 'E':
                    DrawTexturePro(salida, 
                        (Rectangle){170.0f, 50.0f, (float)salida.width - 340.0f,
                        (float)salida.height - 100.0f}, //Origen (imagen completa)
                        (Rectangle){(float)(j*TILE), (float)(i*TILE), (float)(TILE+1), (float)(TILE+1)}, //destino escalado
                        (Vector2){0,0},
                        0.0f,
                        WHITE
                    );
                    break;
                default: TraceLog(LOG_WARNING, "Elemento no conocido");
                    break;
            }
        }
    }
}

//Jugador
void dibujarJugador(int jugadorX, int jugadorY, int camX, int camY){
    int posX = (jugadorX - camX) * TILE;
    int posY = (jugadorY - camY) * TILE;
    DrawTexturePro(jugador,
        (Rectangle){30.f, 50.0f, (float)jugador.width - 60.f,
        (float)jugador.height - 100.0f},
    
        (Rectangle){(float)posX, (float)posY, (float)(TILE), (float)(TILE)},
        (Vector2){0,0}, 0.0f, WHITE);
}

//Cerrar y limpiar al finalizar el programa
void finGraficos(){
    //Quitar todas las texturas cargadas
    UnloadTexture(pared);
    UnloadTexture(camino);
    UnloadTexture(puerta);
    UnloadTexture(moneda);
    UnloadTexture(jugador);
    UnloadTexture(salida);
    CloseWindow();
}