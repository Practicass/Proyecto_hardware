

#include "wd_hal.h"

void WD_hal_inicializar(int sec){
    WDTC = sec * 15000000/4; // 15000 * 1000 ; 1000ms = 1s
    WDMOD = 0x03;
}

void WD_hal_feed(){
    uint32_t irq;
    irq = read_IRQ_bit();
    disable_irq();  
    WDFEED = 0xAA;
    WDFEED = 0X55;
    if(irq != 0){
        enable_irq();
    }       
        
    
    

}

void WD_hal_test(){
    while(1){}  
}

