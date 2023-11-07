#ifndef TEST_H
#define TEST_H


#include "alarmas.h"



void testAlarmas(void);

//test que comprueba la programación de una alarma
void testAlarmas1(void);

//test que comprueba la programación de alarmas periódicas y la eliminación de una alarma
void testAlarmas2(void);


//test que comprueba el limite de alarmas simultaneas
void testAlarmasOverflow(void);

#endif
