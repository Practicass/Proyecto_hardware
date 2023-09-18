//uint8_t conecta_K_buscar_alineamiento_arm(TABLERO *t, uint8_t
//	fila, uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
//	delta_columna);
// comprobar si la celda es valida y del mismo color
		//if (tablero_buscar_color(t, fila, columna, color) != EXITO) {

		//	return 0;
		//}
		
    // encontrada, entonces avanzar índices
    //uint8_t nueva_fila = fila + delta_fila;
    //uint8_t nueva_columna = columna + delta_columna;

    // incrementar longitud y visitar celda vecina
    //return 1 + conecta_K_buscar_alineamiento_c(t, nueva_fila, nueva_columna, color, delta_fila, delta_columna);


    ;PROLOGO
    STMDB R13!, {R2-R12,R14} ; guarda en la pila los valores de los registros previos a la rutina
    MOV R10,R0 ; guarda los parametros a usar en registros usables
    MOV R4,R1
    MOV R5,R2
    MOV R11,R3
    ADD R7,R13,#0x00000030 ;apuntar a la cima de la pila
    LDMIA R7,{R6-R7}

    ;comprobar si la celda es valida y del mismo color
      MOV R3,R11
      MOV R2,R5
      MOV R1,R4
      MOV R0,R10
      BL tablero_buscar_color
    CMP R0,#0x00000000
    BEQ exito
    MOV R0,#0x00000000 ;return 0
    LDMIA R13, {R2-R12,R14}
    BX R14 ;sale de la rutina

  exito 
    ADD R0,R4,R6 ;nueva_fila++
    AND R8,R0,#0x000000FF
    ADD R0,R5,R7 ;nueva_columna++
    AND R9,R0,0x000000FF
    MOV R3,R11
    MOV R2,R9
    MOV R1,R8
    MOV R0,R10
    STMIA R13, {R6-R7}
    BL conecta_K_buscar_alineamiento_arm
    ADD R0,R0,#0x00000001
    AND R0,R0,#0x000000FF
    B
    




// devuelve true si encuentra una línea de longitud mayor o igual a _K
//uint8_t
//conecta_K_hay_linea_arm_c(TABLERO *t, uint8_t fila, uint8_t columna, uint8_t color)
//{
//	 enum { N_DELTAS = 4};
//   int8_t deltas_fila[N_DELTAS] = {0, -1, -1, 1};
//   int8_t deltas_columna[N_DELTAS] = {-1, 0, -1, -1};
//   unsigned int i = 0;
//   uint8_t linea = FALSE;
//   uint8_t long_linea = 0;
//
//    buscar linea en fila, columna y 2 diagonales
//   for(i=0; (i < N_DELTAS) && (linea == FALSE); ++i) {
//       // buscar sentido
//       long_linea = conecta_K_buscar_alineamiento_c(t, fila, columna, color, deltas_fila[i], deltas_columna[i]);
//       linea = long_linea >= K_SIZE;
//       if (linea) {
//         continue;
//       }
//       // buscar sentido inverso
//       long_linea += conecta_K_buscar_alineamiento_c(t, fila-deltas_fila[i],
//	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
//       linea = long_linea >= K_SIZE;
//   }
//   return linea;
//}


STMDB R13!, {R0-R10,R14}
MOV R9,R0
MOV R7,R1
MOV R8,R2
MOV R10,R3
ADD R0, PC, #0x0000011C
LDR R0, [R0]
STR R0,[R13,0x000C]
ADD R0,PC,#0x00000114
LDR R0,[R0]
STR R0,[R13,#0x0008]
MOV R4,#0x00000000
MOV R5,#0x00000000
MOV R6,#0x00000000
NOP
B fin

for
ADD R0,R13,#0x00000008
LDRSB R0,[R0,R4]
ADD R1,R13,#0x0000000C
LDRSB R1,[R1,R4]
MOV R3,R10
MOV R2,R8
STR R1,[R13]
MOV R1,R7
STR R0,[R13,#0X0004]
MOV R0,R9
BL conecta_K_buscar_alineamiento_c
MOV R6,R0
CMP R6,#0x00000004
BLT salto1
MOV R0,#0x00000001
B salto2

salto1
MOV R0,#0x00000000

salto2
MOV R5,R0
CMP R5,#0x00000000
BEQ salir_if
B fin
salir_if 
ADD R0,R13,#0x00000008
LDRB R0,[R0,R4]
RSB R0,R0,#0x00000000
MOV R0,R0,LSL #24
MOV R0,R0,ASR #24
ADD R1,R13,#0x0000000C
LDRB R1,[R1,R4]
RSB R1,R1,#0x00000000
MOV R0,R0,LSL #24
MOV R0,R0,ASR #24
STR R0,[R13,#0X0004]
STR R1,[R13]
ADD R0,R13, #0x00000008
LDRB R0,[R0,R4]
SUB R0,R8,R0 
AND R2,R0,#0x000000FF
ADD R0,R12,#0x0000000C
LDRB R0,[R0,R4]
SUB R0,R7,R0  
AND R1,R0,#0x000000FF
MOV R3,R10 
MOV R0,R9 
BL conecta_K_buscar_alineamiento_c
ADD R0,R0,R6
ADD R6,R0, #0x000000FF
CMP R6, #0x00000004
BLT salto3
MOV R0,#0x00000001
B salto4

salto3
MOV R0,#0x00000000

salto4
MOV R5,R0
NOP 

fin
ADD R4,R4,#0x00000001
CMP R4,#0x00000004
BCS salto5
CMP R5,#0x00000000
BEQ for

salto5
MOV R0,R5
ADD R13,R13,#0x00000010
LDMIA R13!, {R4-R10,R14}
