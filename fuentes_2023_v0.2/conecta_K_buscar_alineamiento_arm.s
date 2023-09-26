	AREA datos,DATA, READWRITE
		
	AREA codigo,CODE, READONLY
	ENTRY
	IMPORT tablero_buscar_color
	EXPORT conecta_K_buscar_alineamiento_arm
	PRESERVE8
		



;conecta_K_buscar_alineamiento_arm

conecta_K_buscar_alineamiento_arm 
    stmdb     r13!,{r4-r12,r14}
    mov       r10,r0; r10=1arg 
    mov       r4,r1; r4=2arg
    mov       r5,r2; r5=3arg
    mov       r11,r3; r11=4arg
    add       r7,r13,#0x00000028; r7= cima pila  
    ldmia     r7,{r6-r7}; r6=
    mov       r3,r11
    mov       r2,r5
    mov       r1,r4
    mov       r0,r10
    stmdb     r13!,{r4-r8,r14}
    mov       r6,r0
    mov       r5,r1
    mov       r7,r2
    mov       r8,r3
    mov       r0,r5
    mov       r1,r0
    cmp       r1,#0x00000007
    bge       jump8
    mov       r0,#0x00000001
     b        jump9
jump8 mov       r0,#0x00000000
    
jump9 cmp       r0,#0x00000000
    beq       jump2
    mov       r0,r7
    
    mov       r1,r0
    cmp       r1,#0x00000007
    bge       jump10
    mov       r0,#0x00000001
    b jump11
jump10 mov       r0,#0x00000000
    
jump11 cmp       r0,#0x00000000
    bne       jump3
jump2 mvn       r0,#0x00000000
jump17 ldmia     r13!,{r4-r8,r14}
    b        jump12
jump3 mov       r4,#0x00000000
    b         jump4
jump6 add       r4,r4,#0x00000001
jump4 cmp       r4,#0x00000006
    bcs       jump5
    add       r0,r5,r5,lsl #1
    add       r0,r6,r0,lsl #1
    ldrb      r0,[r0,r4]
    cmp       r0,r7
    bne       jump6
jump5 cmp       r4,#0x00000006
    bne       jump16
    mvn       r0,#0x00000000
    b         jump7
jump16 add       r1,r5,r5,lsl #1
    add       r2,r6,#0x0000002a
    add       r1,r2,r1,lsl #1
    ldrb      r0,[r1,r4]
    and       r1,r0,#0x00000003
    cmp       r1,r8
    bne       jump7
    mov       r0,#0x00000000
    b         jump17
jump7 mvn       r0,#0x00000000
    b         jump17
jump12 cmp       r0,#0x00000000
    beq       jump20
    mov       r0,#0x00000000
jump1 ldmia     r13!,{r4-r12,r14}
    bx        r14
jump20 add       r0,r4,r6
    and       r8,r0,#0x000000ff
    add       r0,r5,r7
    and       r9,r0,#0x000000ff
    mov       r3,r11
    mov       r2,r9
    mov       r1,r8
    mov       r0,r10
    stmia     r13,{r6-r7}
    bl        conecta_K_buscar_alineamiento_arm
    add       r0,r0,#0x00000001
    and       r0,r0,#0x000000ff
    b         jump1
	
	END