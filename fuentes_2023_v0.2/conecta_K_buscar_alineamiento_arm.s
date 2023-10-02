	AREA datos,DATA, READWRITE
		
	AREA codigo,CODE, READONLY
	ENTRY
	IMPORT tablero_buscar_color
	EXPORT conecta_K_buscar_alineamiento_arm
	PRESERVE8
		



;conecta_K_buscar_alineamiento_arm

conecta_K_buscar_alineamiento_arm 
    STMDB     R13!,{R4-R10,R14}; GUARDA ESTADO ANTERIOR
	MOV  	R8, R1
	MOV		R9,R2
    MOV       R4,#0
hop9    CMP       R8,#0x0007
    BGE       hop1
    CMP       R9,#0x007
    BLT       hop2
hop1 MVN       R5,#0
    B         hop3
hop2    MOV R6, #0
    B hop8
hop5 ADD       R6,R6,#1
hop8 CMP       R6,#6
	BCS       hop4
	;---
	ADD       R7,R8,R8,LSL #1
	ADD       R7,R6,R7,LSL #1
	LDRB      R7,[R0,R7]
	;---
	CMP       R7,R9
	BNE       hop5
hop4 CMP      R6,#6
    BNE       hop6

    MVN       R5,#0
    B       hop3 
hop6 ADD R7,R8,R8,LSL #1
    ADD R10,R0,#0x00002A
    ADD R7,R6,R7,LSL #1
    LDRB R7,[R10,R7]
    ;????
    AND R7,R7,#0x0003
    CMP R7,R3
    BNE hop7

    MOV R5,#0
    ADD R7,R4,#1
    AND R4,R7,#0x0FF

    LDRB R7,[R13,#0x020]
    ADD R7,R8,R7
    AND R8,R7,#0x00000FF 

    LDR R7,[R13,#0x024]
    ADD R7,R9,R7
    AND R9,R7,#0x00000FF 
    B hop3

hop7 MVN R5,#0

hop3 CMP R5, #0
    BEQ hop9
    
    MOV R0,R4
    LDMIA R13!,{R4-R10,R14}
    BX R14

	
	END