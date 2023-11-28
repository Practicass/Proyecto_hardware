
#include "linea_serie_hal.h"

static void (*funcion_callback5)();
static void (*funcion_callback6)();


void linea_serie_ISR() __irq{
    uint32_t iterrupcion = U0IIR;
    if((iterrupcion & 0x0e) == 4){
        funcion_callback5(U0RBR);
    }else if((iterrupcion & 0x0e)==2){
        U0IER = 0x1;
        funcion_callback6();
    }
    VICVectAddr = 0;
}

void linea_serie_inicializar(void (*funcion_callback)(), void (*funcion_callback2)()){
    funcion_callback5 = funcion_callback;
    funcion_callback6 = funcion_callback2;
    PINSEL0 |= 0x5;
    U0LCR = 0x80;
    U0DLL = 91;
    U0LCR = 3;
    U0IER = 0x3;
    VICVectCntl4 = 0x20 | 6;
    VICVectAddr4 = (unsigned long)linea_serie_ISR;
    VICIntEnable |= 0x00000040;

}

void linea_serie_hal(uint8_t caracter){
    U0IER |= 0x2;
    U0THR = caracter;

}

