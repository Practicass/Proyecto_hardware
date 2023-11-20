
#include "linea_serie_hal.h"

void (*funcion_callback5)();
void (*funcion_callback6)();
uint8_t evento5;

void linea_serie_ISR() __irq{
    
    if((U0IIR & 0xe) == 4){
        funcion_callback5(U0RBR);
    }else /*if((U0IIR & 0x02)==2)*/{
        U0IER = 0x1;
        funcion_callback6(evento5);
    }
    VICVectAddr = 0;
}

void linea_serie_inicializar(void (*funcion_callback)(), void (*funcion_callback2)(), uint8_t idEvento){
    funcion_callback5 = funcion_callback;
    funcion_callback6 = funcion_callback2;
    evento5 = idEvento;
    PINSEL0 |= 0x5;
    U0LCR = 0x80;
    U0DLL = 91;
    U0LCR = 3;
    U0IER = 0x1;
    // U0FCR |= 1;
    VICVectCntl4 = 0x20 | 6;
    VICVectAddr4 = (unsigned long)linea_serie_ISR;
    VICIntEnable |= 0x00000040;

}

void linea_serie_hal(uint8_t caracter){
    //U0FCR |= 1;
    U0IER |= 0x2;
    U0THR = caracter;
    
    //U0FCR &= 0x3f;
    // U0FCR &= 0xfe;
    // U0FCR |= 1;
}

