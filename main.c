#include "juego.h"
#include "raylib.h"

int main(){
    //Iniciar el juego
    iniciarJuego();

    //Ciclo para que se mande a llamar la logica de dibujo del mapa y logica del juego
    while(!WindowShouldClose()){
        estadoJuego();
        llamarDibujar();
    }

    //Cerrar Juego
    limpiar();
    return 0;
}