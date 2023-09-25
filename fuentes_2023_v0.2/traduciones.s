//uint8_t conecta_k_buscar_alineamiento_arm(tablero *t, uint8_t
//	fila, uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
//	delta_columna);
// comprobar si la celda es valida y del mismo color
		//if (tablero_buscar_color(t, fila, columna, color) != exito) {

		//	return 0;
		//}
		
    // encontrada, entonces avanzar índices
    //uint8_t nueva_fila = fila + delta_fila;
    //uint8_t nueva_columna = columna + delta_columna;

    // incrementar longitud y visitar celda vecina
    //return 1 + conecta_k_buscar_alineamiento_c(t, nueva_fila, nueva_columna, color, delta_fila, delta_columna);


    ;prologo
    stmdb r13!, {r2-r12,r14} ; guarda en la pila los valores de los registros previos a la rutina
    mov r10,r0 ; guarda los parametros a usar en registros usables
    mov r4,r1
    mov r5,r2
    mov r11,r3
    add r7,r13,#0x00000030 ;apuntar a la cima de la pila
    ldmia r7,{r6-r7}

    ;comprobar si la celda es valida y del mismo color
      mov r3,r11
      mov r2,r5
      mov r1,r4
      mov r0,r10
      
    stmdb r13!,{r4-r8,r14}; prologo
    mov   r6,r0
    mov   r5,r1
    mov   r7,r2
    mov   r8,r3
    mov   r0,r5

    mov   r1,r0; bl    tablero_fila_valida(0x0000075c)
    cmp   r1,#0x00000007
    bge   0x00000770
    mov   r0,#0x00000001

    cmp   r0,#0x00000000
    beq   0x000006d0; salta a return error
    mov   r0,r7

    mov   r1,r0; bl    tablero_columna_valida(0x00000740)
    cmp   r1,#0x00000007
    bge   0x00000754
    mov   r0,#0x00000001

    cmp   r0,#0x00000000
    bne   0x000006dc
    mvn   r0,#0x00000000; return error
    ldmia r13!,{r4-r8,r14}
    bx    r14
    mov   r4,#0x00000000; col = 0
    b     0x000006e8
    add   r4,r4,#0x00000001
    cmp   r4,#0x00000006
    bcs   0x00000704
    add   r0,r5,r5,lsl #1
    add   r0,r6,r0,lsl #1
    ldrb  r0,[r0,r4]
    cmp   r0,r7
    bne   0x000006e4
    cmp   r4,#0x00000006
    bne   0x00000714
    add   r1,r5,r5,lsl #1; celda_color()
    add   r2,r6,#0x0000002a
    add   r1,r2,r1,lsl #1
    ldrb  r0,[r1,r4]
    and   r1,r0,#0x00000003
    cmp   r1,r8
    bne   0x00000738
    mov   r0,#0x00000000
    b     0x000006d4
    mvn   r0,#0x00000000
    b     0x000006d4
    mov   r1,r0
    cmp   r1,#0x00000007
    bge   0x00000754
    mov   r0,#0x00000001
    bx    r14

    cmp r0,#0x00000000
    beq exito
    mov r0,#0x00000000 ;return 0
    ldmia r13, {r2-r12,r14}
    bx r14 ;sale de la rutina

  exito 
    add r0,r4,r6 ;nueva_fila++
    and r8,r0,#0x000000ff
    add r0,r5,r7 ;nueva_columna++
    and r9,r0,0x000000ff
    mov r3,r11
    mov r2,r9
    mov r1,r8
    mov r0,r10
    stmia r13, {r6-r7}
    stmdb r13!,{r4-r8,r14}; prologo
    mov   r6,r0
    mov   r5,r1
    mov   r7,r2
    mov   r8,r3
    mov   r0,r5

    mov   r1,r0; bl    tablero_fila_valida(0x0000075c)
    cmp   r1,#0x00000007
    bge   0x00000770
    mov   r0,#0x00000001

    cmp   r0,#0x00000000
    beq   0x000006d0; salta a return error
    mov   r0,r7

    mov   r1,r0; bl    tablero_columna_valida(0x00000740)
    cmp   r1,#0x00000007
    bge   0x00000754
    mov   r0,#0x00000001

    cmp   r0,#0x00000000
    bne   0x000006dc
    mvn   r0,#0x00000000; return error
    ldmia r13!,{r4-r8,r14}
    bx    r14
    mov   r4,#0x00000000; col = 0
    b     0x000006e8
    add   r4,r4,#0x00000001
    cmp   r4,#0x00000006
    bcs   0x00000704
    add   r0,r5,r5,lsl #1
    add   r0,r6,r0,lsl #1
    ldrb  r0,[r0,r4]
    cmp   r0,r7
    bne   0x000006e4
    cmp   r4,#0x00000006
    bne   0x00000714
    add   r1,r5,r5,lsl #1; celda_color()
    add   r2,r6,#0x0000002a
    add   r1,r2,r1,lsl #1
    ldrb  r0,[r1,r4]
    and   r1,r0,#0x00000003
    cmp   r1,r8
    bne   0x00000738
    mov   r0,#0x00000000
    b     0x000006d4
    mvn   r0,#0x00000000
    b     0x000006d4
    mov   r1,r0
    cmp   r1,#0x00000007
    bge   0x00000754
    mov   r0,#0x00000001
    bx    r14
    add r0,r0,#0x00000001
    and r0,r0,#0x000000ff
    
    




// devuelve true si encuentra una línea de longitud mayor o igual a _k
//uint8_t
//conecta_k_hay_linea_arm_c(tablero *t, uint8_t fila, uint8_t columna, uint8_t color)
//{
//	 enum { n_deltas = 4};
//   int8_t deltas_fila[n_deltas] = {0, -1, -1, 1};
//   int8_t deltas_columna[n_deltas] = {-1, 0, -1, -1};
//   unsigned int i = 0;
//   uint8_t linea = false;
//   uint8_t long_linea = 0;
//
//    buscar linea en fila, columna y 2 diagonales
//   for(i=0; (i < n_deltas) && (linea == false); ++i) {
//       // buscar sentido
//       long_linea = conecta_k_buscar_alineamiento_c(t, fila, columna, color, deltas_fila[i], deltas_columna[i]);
//       linea = long_linea >= k_size;
//       if (linea) {
//         continue;
//       }
//       // buscar sentido inverso
//       long_linea += conecta_k_buscar_alineamiento_c(t, fila-deltas_fila[i],
//	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
//       linea = long_linea >= k_size;
//   }
//   return linea;
//}


stmdb r13!, {r0-r10,r14}
mov r9,r0
mov r7,r1
mov r8,r2
mov r10,r3
add r0, pc, #0x0000011c
ldr r0, [r0]
str r0,[r13,0x000c]
add r0,pc,#0x00000114
ldr r0,[r0]
str r0,[r13,#0x0008]
mov r4,#0x00000000
mov r5,#0x00000000
mov r6,#0x00000000
nop
b fin

for
add r0,r13,#0x00000008
ldrsb r0,[r0,r4]
add r1,r13,#0x0000000c
ldrsb r1,[r1,r4]
mov r3,r10
mov r2,r8
str r1,[r13]
mov r1,r7
str r0,[r13,#0x0004]
mov r0,r9
stmdb r13!,{r4-r8,r14}; prologo
mov   r6,r0
mov   r5,r1
mov   r7,r2
mov   r8,r3
mov   r0,r5

mov   r1,r0; bl    tablero_fila_valida(0x0000075c)
cmp   r1,#0x00000007
bge   0x00000770
mov   r0,#0x00000001

cmp   r0,#0x00000000
beq   0x000006d0; salta a return error
mov   r0,r7

mov   r1,r0; bl    tablero_columna_valida(0x00000740)
cmp   r1,#0x00000007
bge   0x00000754
mov   r0,#0x00000001

cmp   r0,#0x00000000
bne   0x000006dc
mvn   r0,#0x00000000; return error
ldmia r13!,{r4-r8,r14}
bx    r14
mov   r4,#0x00000000; col = 0
b     0x000006e8
add   r4,r4,#0x00000001
cmp   r4,#0x00000006
bcs   0x00000704
add   r0,r5,r5,lsl #1
add   r0,r6,r0,lsl #1
ldrb  r0,[r0,r4]
cmp   r0,r7
bne   0x000006e4
cmp   r4,#0x00000006
bne   0x00000714
add   r1,r5,r5,lsl #1; celda_color()
add   r2,r6,#0x0000002a
add   r1,r2,r1,lsl #1
ldrb  r0,[r1,r4]
and   r1,r0,#0x00000003
cmp   r1,r8
bne   0x00000738
mov   r0,#0x00000000
b     0x000006d4
mvn   r0,#0x00000000
b     0x000006d4
mov   r1,r0
cmp   r1,#0x00000007
bge   0x00000754
mov   r0,#0x00000001
bx    r14
mov r6,r0
cmp r6,#0x00000004
blt salto1
mov r0,#0x00000001
b salto2

salto1
mov r0,#0x00000000

salto2
mov r5,r0
cmp r5,#0x00000000
beq salir_if
b fin
salir_if 
add r0,r13,#0x00000008
ldrb r0,[r0,r4]
rsb r0,r0,#0x00000000
mov r0,r0,lsl #24
mov r0,r0,asr #24
add r1,r13,#0x0000000c
ldrb r1,[r1,r4]
rsb r1,r1,#0x00000000
mov r0,r0,lsl #24
mov r0,r0,asr #24
str r0,[r13,#0x0004]
str r1,[r13]
add r0,r13, #0x00000008
ldrb r0,[r0,r4]
sub r0,r8,r0 
and r2,r0,#0x000000ff
add r0,r12,#0x0000000c
ldrb r0,[r0,r4]
sub r0,r7,r0  
and r1,r0,#0x000000ff
mov r3,r10 
mov r0,r9 
stmdb r13!,{r4-r8,r14}; prologo
mov   r6,r0
mov   r5,r1
mov   r7,r2
mov   r8,r3
mov   r0,r5

mov   r1,r0; bl    tablero_fila_valida(0x0000075c)
cmp   r1,#0x00000007
bge   0x00000770
mov   r0,#0x00000001

cmp   r0,#0x00000000
beq   0x000006d0; salta a return error
mov   r0,r7

mov   r1,r0; bl    tablero_columna_valida(0x00000740)
cmp   r1,#0x00000007
bge   0x00000754
mov   r0,#0x00000001

cmp   r0,#0x00000000
bne   0x000006dc
mvn   r0,#0x00000000; return error
ldmia r13!,{r4-r8,r14}
bx    r14
mov   r4,#0x00000000; col = 0
b     0x000006e8
add   r4,r4,#0x00000001
cmp   r4,#0x00000006
bcs   0x00000704
add   r0,r5,r5,lsl #1
add   r0,r6,r0,lsl #1
ldrb  r0,[r0,r4]
cmp   r0,r7
bne   0x000006e4
cmp   r4,#0x00000006
bne   0x00000714
add   r1,r5,r5,lsl #1; celda_color()
add   r2,r6,#0x0000002a
add   r1,r2,r1,lsl #1
ldrb  r0,[r1,r4]
and   r1,r0,#0x00000003
cmp   r1,r8
bne   0x00000738
mov   r0,#0x00000000
b     0x000006d4
mvn   r0,#0x00000000
b     0x000006d4
mov   r1,r0
cmp   r1,#0x00000007
bge   0x00000754
mov   r0,#0x00000001
bx    r14
add r0,r0,r6
add r6,r0, #0x000000ff
cmp r6, #0x00000004
blt salto3
mov r0,#0x00000001
b salto4

salto3
mov r0,#0x00000000

salto4
mov r5,r0
nop 

fin
add r4,r4,#0x00000001
cmp r4,#0x00000004
bcs salto5
cmp r5,#0x00000000
beq for

salto5
mov r0,r5
add r13,r13,#0x00000010
ldmia r13!, {r4-r10,r14}
