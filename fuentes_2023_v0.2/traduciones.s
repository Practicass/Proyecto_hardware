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
    STMDB r13!, {R2-R12,R14} ; guarda en la pila los valores de los registros previos a la rutina
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
    MOV R0,10
    BL tablero_buscar_color
    CMP R0,#0x00000000
    BEQ no_exito
    MOV R0,#0x00000000 ;return 0
    LDMIA R13, {R2-R12,R14}
    BX R14 ;sale de la rutina
    



    