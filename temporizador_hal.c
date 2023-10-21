
#include <LPC210X.H>  
#include "temporizador_hal.h"
  

static volatile unsigned int timer0_int_count = 0;
static volatile unsigned int timer1_int_count = 0;
static void (*funcion_callback1)();

void timer0_ISR (void) __irq;    // Generate Interrupt 

void timer_ISR (void) __irq {
    timer0_int_count++;
    T0IR = 1;                              // Clear interrupt flag
    VICVectAddr = 0;                            // Acknowledge Interrupt
}
void timer1_ISR (void) __irq {
	
    funcion_callback1();
    T1IR = 1;                              // Clear interrupt flag
    VICVectAddr = 0;                            // Acknowledge Interrupt
}

void temporizador_hal_iniciar(){
    timer0_int_count = 0;
		
	// configuration of Timer 0
    T0PR = 2999;
	T0MR0 = 10000;  // Interrumpe cada 0,05ms = 150.000-1 counts
    T0MCR = 3;                     // Generates an interrupt and resets the count when the value of MR0 is reached
    T0TCR = 1;                             // Timer0 Enable
    // configuration of the IRQ slot number 0 of the VIC for Timer 0 Interrupt
		VICVectAddr0 = (unsigned long)timer_ISR;          // set interrupt vector in 0
    // 0x20 bit 5 enables vectored IRQs. 
		// 4 is the number of the interrupt assigned. Number 4 is the Timer 0 (see table 40 of the LPC2105 user manual  
		VICVectCntl0 = 0x20 | 4;  

}
/* T  T0TCR = 1;  imer Counter 0 Interrupt executes each 10ms @ 60 MHz CPU Clock */




void temporizador_hal_empezar(){
    T0TCR = 1;
    VICIntEnable = VICIntEnable | 0x10;
    timer0_int_count = 0;
    T0TC = 0;
    T0PC = 0;
}

uint64_t temporizador_hal_leer(){
    return timer0_int_count * 10000*TEMPORIZADOR_HAL_TICKS2US + T0TC*TEMPORIZADOR_HAL_TICKS2US + T0PC;
}

uint64_t temporizador_hal_parar(){
    T0TCR = 0;
    return temporizador_hal_leer();
}





void temporizador1_hal_iniciar(uint32_t periodo, void
(*funcion_callback)()){
		funcion_callback1 = funcion_callback;
		timer1_int_count = 0;                   
		T1PR = 2999999;
		T1MR0 = periodo;
    T1MCR = 3;
		T1TCR = 1;
		VICVectAddr0 = (unsigned long)timer1_ISR;
		VICVectCntl0 = 0x20 | 5;


}

uint64_t temporizador1_hal_leer(){
    return timer1_int_count * 10000*TEMPORIZADOR_HAL_TICKS2US + T0TC*TEMPORIZADOR_HAL_TICKS2US + T0PC;
}

uint64_t temporizador1_hal_parar(){
    T0TCR = 0;
    return temporizador_hal_leer();
}

void temporizador1_hal_empezar(){
    T1TCR = 1;
    VICIntEnable = VICIntEnable | 0x20;
    timer1_int_count = 0;
    T1TC = 0;
    T1PC = 0;
}


void temporizador_hal_reloj (uint32_t periodo, void
(*funcion_callback)()){
	if(periodo == 0){
		temporizador1_hal_parar();
	}else{
		temporizador1_hal_iniciar(periodo, funcion_callback);
		temporizador1_hal_empezar();
		
	}	
}


