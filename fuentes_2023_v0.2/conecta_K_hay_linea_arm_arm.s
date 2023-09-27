	AREA datos,DATA, READWRITE
		
	AREA codigo,CODE, READONLY
	ENTRY
	IMPORT conecta_K_buscar_alineamiento_arm
	EXPORT conecta_K_hay_linea_arm_arm
	PRESERVE8


conecta_K_hay_linea_arm_arm
	stmdb r13!, {r4-r10,r14}; guarda el estado
	mov r9, r0; r9=tablero
	mov r7, r1; r7=fila
	mov r8, r2; r8=columna
	
	;add r9, PC, #0x0000011C; r0=0x578

	;deltas_fila[N_DELTAS] = {0, -1, -1, 1}, &deltas_fila = 0x4000043C
	mov r5, #0x01000000
	add r5, r5, #0x00ff0000
	add r5, r5, #0x0000ff00
	
	mov r10, #0
	mov r6, #0x40
	add r10, r10, r6, lsl #24
	add r10, r10, r6, lsl #4
	mov r6, #0x38
	add r10, r6, r10
	
	str r5, [r10] ;int8_t deltas_columna[N_DELTAS] = {-1, 0, -1, -1}; &deltas_columna = 0x40000438
	mov r5, #0xff00ffff
	str r5, [r10, #4]

	; no hace falta?? mov r10, r3; r10=color
	mov r4, #0x00000000 ;r4=i=0
	mov r5, #0x00000000 ;r5=linea
	mov r6, #0x00000000 ;r6=long_linea
	
	nop

	add r4,r4,#0x00000001 ; i++
	cmp r4,#0x00000004 ;(i < N_DELTAS)
	bcs fin_for
	cmp r5,#0x00000000 ;(linea == FALSE)
	bne fin_for
for
	add r9, r10, #0x00000004 ; r0=&deltas_columna
	ldrsb r9,[r9] ; r9=deltas_columna[i]
	mov r7,r10 ; r7=&deltas_fila
	ldrsb r7,[r7] ; r1=deltas_fila[i]
	;no hace falta? mov r3,r10; r3=color
	;no hace falta? mov r2,r8
	str r7,[r13] ;pasa el argumento deltas_fila[i] por pila
	; mov r1,r7 se ha cambiado el r1 por r7 en instrucciones anteriores
	str r9,[r13,#0X0004] ;pasa el argumento deltas_columna[i] por pila
	;mov r0,r9; se ha cambiado el r0 por r9 en instrucciones anteriores
	;actualizar cima pla
	bl conecta_K_buscar_alineamiento_arm
	mov r6,r0
	cmp r6,#0x00000004
	blt salto1
	mov r0,#0x00000001
	b salto2

salto1	mov r0,#0x00000000

salto2 mov r5,r0
	cmp r5,#0x00000000
	beq salir_if
	b fin_for
salir_if add r0,r13,#0x00000008
	ldrb r0,[r0,r4]
	rsb r0,r0,#0x00000000
	mov r0,r0,LSL #24
	mov r0,r0,ASR #24
	add r1,r13,#0x0000000C
	ldrb r1,[r1,r4]
	rsb r1,r1,#0x00000000
	mov r0,r0,LSL #24
	mov r0,r0,ASR #24
	str r0,[r13,#0X0004]
	str r1,[r13]
	add r0,r13, #0x00000008
	ldrb r0,[r0,r4]
	sub r0,r8,r0 
	and r2,r0,#0x000000FF
	add r0,r12,#0x0000000C
	ldrb r0,[r0,r4]
	sub r0,r7,r0  
	and r1,r0,#0x000000FF
	mov r3,r10 
	mov r0,r9 
	bl conecta_K_buscar_alineamiento_arm
	add r0,r0,r6
	add r6,r0, #0x000000FF
	cmp r6, #0x00000004
	blt salto3
	mov r0,#0x00000001
	b salto4

salto3 mov r0,#0x00000000

salto4	mov r5,r0
	nop 

fin_for	mov r0,r5
	add r13,r13,#0x00000010
	ldmia r13!, {r4-r10,r14}
	bx r14
	END