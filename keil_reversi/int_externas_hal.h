#ifndef INT_EXTERNAS_HAL
#define INT_EXTERNAS_HAL

#include "fifo.h"
#include <LPC210X.H>     

void eint1_ISR (void) __irq;

void eint2_ISR (void) __irq;

void eint1_init (void);

void eint2_init (void);


void eint1_enable(void);
void eint2_enable(void);

unsigned int eint1_hold(void);
unsigned int eint2_hold(void);



#endif
