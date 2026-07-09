# BitQuest
Videojuego 2D desarrollado en **C** y **NASM x86-64** utilizando la biblioteca gráfica **Raylib**.

El proyecto integra programación de alto y bajo nivel para la construcción de un motor de juego modular, combinando lógica de juego implementada en C con rutinas de procesamiento desarrolladas en lenguaje ensamblador.

## Objetivo
Desarrollar un videojuego 2D que integrara programación en C y lenguaje ensamblador NASM x86-64 para aplicar conceptos de programación de sistemas, desarrollo de videojuegos e interacción entre software de alto y bajo nivel.

## Tecnologías utilizadas

* C
* NASM x86-64
* Raylib
* GCC
* Linux

## Características

* Arquitectura modular.
* Integración entre C y ensamblador.
* Renderizado gráfico mediante Raylib.
* Compilación multiplataforma en entornos Linux.
* Separación entre componentes gráficos, lógica del juego y procesamiento de bajo nivel.

## Estructura del proyecto

* `main.c` - Punto de entrada del programa.
* `juego.c` - Lógica principal del juego.
* `graficos.c` - Renderizado y manejo gráfico.
* `procesos.asm` - Rutinas desarrolladas en NASM x86-64.
* `build.sh` - Script de compilación.

## Compilación

El repositorio incluye un script denominado `build.sh`.

Para compilar el proyecto:

```bash
chmod +x build.sh
./build.sh
```

## Ejecución

Una vez compilado el proyecto, ejecutar:

```bash
./BitQuest
```

## Conocimientos implementados

Durante el desarrollo de BitQuest se reforzaron conocimientos en:

* Programación en C.
* Programación en lenguaje ensamblador NASM x86-64.
* Integración entre código ensamblador y C.
* Desarrollo modular de software.
* Uso de bibliotecas gráficas mediante Raylib.
* Proceso de compilación y enlazado en entornos Linux.

## Autores

* Suárez Vega, Vladimir
* Zermeño Ojeda, Paola
* Zermeño Ojeda, Diana Valeria
