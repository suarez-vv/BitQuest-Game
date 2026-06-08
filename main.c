#include "juego.h"
#include "raylib.h"

int main(){
    //Iniciar el juego
    iniciarJuego();
    bool status = true;

    //Ciclo para que se mande a llamar la logica de dibujo del mapa, musica y logica del juego
    while(!WindowShouldClose()){
        estadoJuego();
        llamarDibujar(&status);

        if(!status){ //Si el status es verdadero continua el ciclo, si es falso se cierra el juego
            break;
        }
    }

    //Cerrar Juego
    limpiar();
    return 0;
}