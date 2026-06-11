# BitQuest-Proyecto-Final-Lenguaje-Ensamblador
Repositorio de proyecto dedicado a realizarun juego "BitQuest" mediante código híbrido de lenguaje ensamblador y C.

Este programa fue escrito en un sistema operativo Linux Mint 22.3, por lo que para las instrucciones de compilación de usaron las establecidas para linux.
Se creo un script “build.sh” el cual se encuentra en la carpeta del repositorio que al ejecutarlo, ejecuta las instrucciones de compilación de NASM:

nasm -f elf64 *".asm" -o "procesos".o


De compilación de los archivos de C:

gcc -c main.c juego.c graficos.c

Y por último el ensamblado de los archivos:

gcc main.o juego.o graficos.o procesos.o -o "BitQuest" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

Por lo que para realizar la compilación del programa solo hay que ejecutar dicho script desde la terminal:

./build.sh

Y el programa ya ensamblado se guarda con el nombre “BitQuest”, y de igual manera solo hay que ejecutarlo desde la terminal:

./BitQuest