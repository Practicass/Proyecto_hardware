
#include "planificador.h"



void planificador(){
    EVENTO_T idEvento;
		uint32_t auxData;
		
	

    //Inicializar la cola 
    FIFO_inicializar(GPIO_OVERFLOW);

		botones_init();

    //hello_world_inicializar(GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS, GPIO_HAL_PIN_DIR_OUTPUT);
	
		alarma_inicializar();
		
		//alarma_activar(HELLOWORLD, 0x8000000a,0);
    //Bucle infinito pendiente de eventos 
    while(idEvento != ALARMA_OVERFLOW){
			//uint8_t hayEvento = 0; //descomentar comprobar overflow
       uint8_t hayEvento =  FIFO_extraer(&idEvento, &auxData); //comentar para comprobar overflow
			
       if (hayEvento != 0) {
				 if(idEvento == HELLOWORLD){
        
						hello_world_tick_tack();
					}
          else if(idEvento == ALARMA_OVERFLOW){
            gpio_hal_escribir( GPIO_OVERFLOW, GPIO_OVERFLOW_BITS,  GPIO_HAL_PIN_DIR_OUTPUT);
          }else if(idEvento == TIMER){
						alarma_tratar_evento();
			}else if(idEvento == BOTON){
				botones_pulsar(auxData);
			}else if(idEvento == BOTON_EINT1_ALARM || idEvento == BOTON_EINT2_ALARM){
				botones_monitorizar(idEvento);
			}
		
				}else{
					power_hal_wait();
				}
       
    }
}
