	AREA datos,DATA, READWRITE
		
	AREA codigo,CODE, READONLY
	ENTRY
	IMPORT tablero_buscar_color
	EXPORT conecta_K_buscar_alineamiento_arm
	PRESERVE8
		



;conecta_K_buscar_alineamiento_arm

conecta_K_buscar_alineamiento_arm 
	stmdb r13!, {r2-r12,r14} ; guarda en la pila los valores de los registros previos a la rutina
    mov r10, r0 ; guarda los parametros a usar en registros usables
    mov r4, r1
    mov r5, r2
    mov r11, r3
    add r7, r13, #0x00000030 ;apuntar a la cima de la pila
    ldmia r7, {r6-r7}

    
    mov r3, r11 ; comprobar si la celda es valida y del mismo color
    mov r2, r5
    mov r1, r4
    mov r0, r10
    bl tablero_buscar_color
    cmp r0, #0x00000000
    beq exito
    mov r0,#0x00000000 ;return 0
salto    ldmia r13!, {r2-r12,r14}
    bx r14 ;sale de la rutina

exito add r0, r4, r6 ;nueva_fila++
    and r8, r0, #0x000000FF
    add r0, r5, r7 ;nueva_columna++
    and r9, r0, #0x000000FF
    mov r3, r11
    mov r2, r9
    mov r1, r8
    mov r0, r10
    stmia r13, {r6-r7}
    bl conecta_K_buscar_alineamiento_arm
    add r0, r0, #0x00000001
    and r0, r0, #0x000000FF
    b salto
	
	END