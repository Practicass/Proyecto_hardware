    AREA datos, DATA, READWRITE
deltas_fila     EQU     0x00ffff01
deltas_columna  EQU     0xff00ffff
n_deltas        EQU     4
k_size          EQU     4
num_filas       EQU     7
num_columnas    EQU     7
max_no_cero     EQU     6
	AREA codigo,CODE, READONLY
	ENTRY
	IMPORT conecta_K_buscar_alineamiento_c
	EXPORT conecta_K_hay_linea_arm_c
	PRESERVE8


conecta_K_hay_linea_arm_c
	STMDB     R13!,{R4-R10,R14}
	SUB 	R13,R13,#0x0010
	MOV       R9,R0
	MOV       R7,R1
	MOV       R8,R2
	MOV       R10,R3
	LDR       R0,=deltas_fila
	STR       R0,[R13,#0x000C]
	LDR       R0,=deltas_columna
	STR       R0,[R13,#0x0008]
	MOV       R4,#0x00000000
	MOV       R5,#0x00000000
	MOV       R6,#0x00000000
	NOP       
	B         salto1
salto8	ADD       R0,R13,#0x00000008
	LDRSB     R0,[R0,R4]
	ADD       R1,R13,#0x0000000C
	LDRSB     R1,[R1,R4]
	MOV       R3,R10
	MOV       R2,R8
	STR       R1,[R13]
	MOV       R1,R7
	STR       R0,[R13,#0x0004]
	MOV       R0,R9
	BL        conecta_K_buscar_alineamiento_c
	MOV       R6,R0
	CMP       R6,#0x00000004
	BLT       salto2
	MOV       R0,#0x00000001
	B         salto3
salto2	MOV       R0,#0x00000000
salto3	MOV       R5,R0
	CMP       R5,#0x00000000
	BEQ       salto4
	B         salto5
salto4	ADD       R0,R13,#0x00000008
	LDRB      R0,[R0,R4]
	RSB       R0,R0,#0x00000000
	MOV       R0,R0,LSL #24
	MOV       R0,R0,ASR #24
	ADD       R1,R13,#0x0000000C
	LDRB      R1,[R1,R4]
	RSB       R1,R1,#0x00000000
	MOV       R1,R1,LSL #24
	MOV       R1,R1,ASR #24
	STR       R0,[R13,#0x0004]
	STR       R1,[R13]
	ADD       R0,R13,#0x00000008
	LDRB      R0,[R0,R4]
	SUB       R0,R8,R0
	AND       R2,R0,#0x000000FF
	ADD       R0,R13,#0x0000000C
	LDRB      R0,[R0,R4]
	SUB       R0,R7,R0
	AND       R1,R0,#0x000000FF
	MOV       R3,R10
	MOV       R0,R9
	BL        conecta_K_buscar_alineamiento_c
	ADD       R0,R0,R6
	AND       R6,R0,#0x000000FF
	CMP       R6,#0x00000004
	BLT       salto6
	MOV       R0,#0x00000001
	B         salto7
salto6	MOV       R0,#0x00000000
salto7	MOV       R5,R0
	NOP       
salto5	ADD       R4,R4,#0x00000001
salto1	CMP       R4,#0x00000004
	BCS       salto9
	CMP       R5,#0x00000000
	BEQ       salto8
salto9	MOV       R0,R5
	ADD       R13,R13,#0x00000010
	LDMIA     R13!,{R4-R10,R14}
	BX        R14
	
	END