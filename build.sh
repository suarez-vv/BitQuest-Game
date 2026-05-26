#!/bin/bash

#Compilación del archivo ASM
if nasm -f elf641 *".asm" -o "procesos".o; then
    echo ""
    echo "Archivo ASM compilado correctamente"
    echo ""
else
    echo ""
    echo "Hubo un error en la compilación del archivo ASM."
    echo ""
    read aux
    exit 1;
fi

#Compilación del archivo C
if gcc -c main.c juego.c graficos.c; then
    echo ""
    echo "Archivos de C compilados correctamente."
    echo ""
else
    echo ""
    echo "Hubo un error en la compilación de los archivos de C."
    echo ""
    read aux
    exit 1;
fi

#Enlace entre archivos C y ASM
if gcc main.o juego.o graficos.o procesos.o -o "BitQuest" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11; then
    echo "Enlace entre archivosy creación de ejecutable, correcto."
    echo ""
else
    echo ""
    echo "Hubo un error en el enlace de los archivos y/o creación del ejecutable."
    echo ""
    read aux
    exit 1
fi

read -n 1 -s