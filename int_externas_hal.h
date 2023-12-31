#ifndef INT_EXTERNAS_HAL
#define INT_EXTERNAS_HAL

#include "eventos.h"
#include <LPC210X.H>    
#include <inttypes.h> 

void eint1_ISR (void) __irq;

void eint2_ISR (void) __irq;

void eint1_init (void (*funcion_callbackAlarmasParam)());

void eint2_init (void (*funcion_callbackAlarmasParam)());


void eint1_enable(void);
void eint2_enable(void);

unsigned int eint1_hold(void);
unsigned int eint2_hold(void);



#endif
