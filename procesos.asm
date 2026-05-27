bits 64
default rel
global contarAcumulables, actualizarMapa, abrirPuerta, calcularPuntaje
section .text

contarAcumulables:
    ;rdi = mapa
    ;rsi = posicion siguinete (seleccionada) en el mapa

    test rdi, rdi
    jz .fin_contarAcum

    mov r8b, [rdi+rsi]        ; leer caracter siguiente en el mapa

    cmp r8b, 'M'          ; comparar con moneda
    je .moneda

    cmp r8b, 'K'          ; comparar con llave
    je .llave

    cmp r8b, 'D'          ; comparar con puerta
    je .puerta

    cmp r8b, 'E'          ; comparar con salida
    je  .salida

    cmp r8b, '#'          ; comparar con pared
    je  .pared

    jmp .piso

    .moneda:
        mov eax, 0
        jmp .fin_contarAcum

    .llave:
        mov eax, 1
        jmp .fin_contarAcum

    .puerta:
        mov eax, 2
        jmp .fin_contarAcum

    .salida:
        mov eax, 3
        jmp .fin_contarAcum

    .pared:
        mov eax, 4
        jmp .fin_contarAcum
    
    .piso:
        mov eax, 5

    .fin_contarAcum:
        ret

actualizarMapa:
    ; rdi = mapa
    ; rsi = posicion actual en el mapa
    ; rdx = posicion siguiente (seleccionada) en el mapa

    mov r8b, [rdi+rdx]        ; leer caracter siguiente en el mapa (respaldo)
    mov al, [rdi+rsi]         ;obtener el caracter del personaje (posicion actual en el mapa)

    mov [rdi+rdx], al
    mov byte ptr [rdi+rsi], '.'

    .fin_actMapa:
        RET

abrirPuerta:
    ;edi = numero de llaves que tiene el jugador
    CMP EDI, 1
    JGE .abrir
    JMP .no_abrir

    .abrir:
        MOV EAX, 1
        JMP .fin_abrir_puerta
    
    .no_abrir:
        MOV EAX, 0

    .fin_abrir_puerta:
        RET

calcularPuntaje:
    ; edi = monedas
    ; esi = llaves
    ; edx = pasos

    ;monedas * 100 (por decidir)
    mov eax, edi
    ;imul eax, 100

    ;llaves * 500 (por decidir)
    mov r8d, esi
    ;imul r8d, 500

    ;sumar
    add eax, r8d

    ;pasos * 2 (por decidir)
    mov r9d, edx
    ;imul r9d, 2  ;por 2 para penalizar si da muchos pasos 

    ;restar pasos
    sub eax, r9d ;retornar el puntaje final

    ret
