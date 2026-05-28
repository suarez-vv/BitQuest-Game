bits 64
default rel
global contarCaracter, validarMovimiento, calcularPuntaje, detectarObjeto, contarCeldasLibres, actualizarMapa
section .text

;--------------- CONTAR UN CARACTER ESPECIFICO --------------------
contarCaracter:
    ;rdi = mapa
    ;esi = total celdas
    ;edx = caracter buscado
    TEST    RDI, RDI
    JZ      .fin_contarCaracter

    XOR     EAX, EAX
    MOV     R9B, EDX
    MOV     R10B, ESI ;Contador de celdas

    .loop_recorrer:
        CMP     R10B, 0
        JMP     .fin_contarCaracter

        MOV     R11B, [RDI]
        CMP     R11B, R9B
        JNE     .siguiente
        
        INC EAX

    .siguiente:
        INC     RDI
        DEC     R10B
        JMP     .loop_recorrer

    .fin_contarCaracter:
        RET

;--------------- VALIDAR QUE NO SE MUEVA HACIA UNA PARED --------------------
validarMovimiento:
    ;rdi = mapa
    ;esi = numero de columnas/filas en el mapa
    ;edx = Propuesta de nueva fila
    ;ecx = Propuesta de nueva columna

    TEST    RDI, RDI
    JZ      .fin_validarMovimiento
    ;Calcular indice
    MOV     EAX, EDX
    IMUL    EAX, ESI
    ADD     EAX, ECX

    ;Convertir indice a desplazamiento
    MOVSXD  RAX, EAX
    MOV     R10B, [RDI + RAX]

    CMP     R10B, '#'
    JE     .es_pared

    MOV     EAX, 1 ;Si no es pared devolvemos un 1
    JMP     .fin_validarMovimiento

    .es_pared
        MOV EAX, 0 ;Si es pared devolvemos un cero

    .fin_validarMovimiento:
        RET

;--------------- CALCULAR PUNTAJE FINAL --------------------
calcularPuntaje:
    ; edi = monedas
    ; esi = pasos (llaves esta en duda)
    ; edx = numero de niveles completados

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

;--------------- DETECTAR LLAVES, MONEDAS, PUERTA,  SALIDA Y PISO --------------------
detectarObjeto:
    ;rdi = Mapa
    ;esi = Numero de columnas/filas en el mapa
    ;edx = Propuesta de nueva fila
    ;ecx = Propuesta de nueva columna
    ;r8 = Caracter a comparar

    test rdi, rdi
    jz .fin_detectarObjeto

    ;Calcular indice
    mov     eax, edx
    IMUL    eax, esi
    ADD     eax, ecx

    MOVSXD  rax, eax
    MOV     r10b, [rdi + rax]

    cmp r10b, 'M'          ; comparar con moneda
    je .detectado

    cmp r10b, 'K'          ; comparar con llave
    je .detectado

    cmp r10b, 'D'          ; comparar con puerta
    je .detectado

    cmp r10b, 'E'          ; comparar con salida
    je  .detectado

    cmp r10b, '.'           ;Comparar con piso
    je  .detectado

    mov eax, 0
    jmp .fin_detectarObjeto

    .detectado:
        mov eax, 1
        jmp .fin_detectarObjeto

    .fin_detectarObjeto:
        ret

;--------------- CONTAR LA CANTIDAD DE CELDAS DISPONIBLES PARA MOVERSE --------------------
contarCeldasLibres:
    ;rdi = mapa
    ;esi = total de celdas

    xor eax, eax          ;contador = 0

.loop:
    cmp esi, 0
    jle .fin_contar

    mov r8b, [rdi]        ;leer caracter actual

    cmp r8b, '.'          ;comparar con piso
    jne .noCoincide

    inc eax               ;contador++

.noCoincide:

    inc rdi               ;siguiente celda
    dec esi               ;total--

    jmp .loop

.fin_contar:
    ret

;--------------- ACTUALIZAR EL MAPA LUEGO DE HACER UN MOVIMIENTO --------------------
actualizarMapa:
    ; rdi = Mapa
    ; esi = Numero columnas/filas
    ; edx = Fila actual 
    ; ecx = Columna actual
    ; r8 = Fila destino 
    ; r9 = Columna destino

    TEST    RDI, RDI
    JZ      .fin_actMapa

    ;Indice de la posicion actual
    MOV     EAX, EDX
    IMUL    EAX, ESI
    ADD     EAX, ECX

    MOVSXD  RAX, EAX
    LEA     R10, [RDI + RAX] ;Posicion actual del jugador

    ;Indice de la posicion a mover
    MOV     EAX, R8
    IMUL    EAX, ESI
    ADD     EAX, R9

    MOVSXD  RAX, EAX
    LEA     R11, [RDI + RAX] ;Posicion donde el jugador quiere moverse

    MOV AL, [R10]         ;obtener el caracter del personaje (posicion actual en el mapa)

    MOV [R11], AL
    MOV byte ptr [R10], '.'

    .fin_actMapa:
        RET