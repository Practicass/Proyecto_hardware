	AREA datos,DATA, READWRITE
		
	AREA codigo,CODE, READONLY
	ENTRY
	IMPORT conecta_K_buscar_alineamiento_arm
	EXPORT conecta_K_hay_linea_arm_arm
	PRESERVE8


conecta_K_hay_linea_arm_arm
	stmdb r13!, {r0-r10,r14}
	mov r9, r0
	mov r7, r1
	mov r8, r2
	mov r10, r3
	add r0, PC, #0x0000011C
	ldr r0, [r0]
	str r0, [r13, #0x000C]
	add r0, PC, #0x00000114
	ldr r0, [r0]
	str r0, [r13,#0x0008]
	mov r4, #0x00000000
	mov r5, #0x00000000
	mov r6, #0x00000000
	nop
	b fin

for add r0, r13, #0x00000008
	ldrsb r0,[r0,r4]
	add r1,r13,#0x0000000C
	ldrsb r1,[r1,r4]
	mov r3,r10
	mov r2,r8
	str r1,[r13]
	mov r1,r7
	str r0,[r13,#0X0004]
	mov r0,r9
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
	b fin
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

fin	add r4,r4,#0x00000001
	cmp r4,#0x00000004
	bcs salto5
	cmp r5,#0x00000000
	beq for

salto5	mov r0,r5
	add r13,r13,#0x00000010
	ldmia r13!, {r4-r10,r14}
	bx r14
	END