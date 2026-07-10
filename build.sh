#!/bin/bash

#Entrar a la carpeta de código
if cd src; then
    echo ""
    echo "Se ingresó a la carpeta de código del proyecto"
    echo ""
else
    echo ""
    echo "Hubo un al entrar en la carpeta de código."
    echo ""
    read aux
    exit 1;
fi

#Compilación del archivo ASM
if nasm -f elf64 *".asm" -o "procesos".o; then
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

#Crear carpeta bin para el juego final
mkdir -p ../bin

#Enlace entre archivos C y ASM
if gcc main.o juego.o graficos.o procesos.o -o "../bin/BitQuest" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11; then
    echo "Enlace entre archivos y creación de ejecutable, correcto."
    echo ""
else
    echo ""
    echo "Hubo un error en el enlace de los archivos y/o creación del ejecutable."
    echo ""
    rm -r ../bin
    read aux
    exit 1
fi

rm -f *.o

read -n 1 -s