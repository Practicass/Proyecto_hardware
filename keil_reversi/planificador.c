
#include "planificador.h"



void planificador(){
    EVENTO_T idEvento;
		uint32_t auxData;
	

    //Inicializar la cola 
    FIFO_inicializar(GPIO_OVERFLOW);

    hello_world_inicializar(GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS, GPIO_HAL_PIN_DIR_OUTPUT);
    

    //Bucle infinito pendiente de eventos 
    while(1){
			//uint8_t hayEvento = 0; //descomentar comprobar overflow
       uint8_t hayEvento =  FIFO_extraer(&idEvento, &auxData); //comentar para comprobar overflow
			
       if (hayEvento != 0) {
				 if(idEvento == HELLOWORLD){
        
						hello_world_tick_tack();
					}
				}else{
					power_hal_wait();
				}
       
    }
}
