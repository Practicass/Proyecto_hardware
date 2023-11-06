
#include "planificador.h"





void planificador(){
    EVENTO_T idEvento;
		uint32_t auxData;
		
	
	// inicializar gpio
    gpio_hal_iniciar();
    //Inicializar la cola 
	
    FIFO_inicializar(GPIO_OVERFLOW);
	alarma_inicializar();
	hello_world_inicializar(GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS, GPIO_HAL_PIN_DIR_OUTPUT);

	botones_init();

    
	visualizarInicializar();
	

		
		//alarma_activar(HELLOWORLD, 0x8000000a,0);
    //Bucle infinito pendiente de eventos 
	alarma_activar(DEEP_SLEEP, USUARIO_AUSENTE, 0);
	testAlarmas1();
	
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
				alarma_activar(DEEP_SLEEP, USUARIO_AUSENTE, 0);
				juego_tratar_evento(idEvento, auxData);
			}else if(idEvento == BOTON_EINT1_ALARM || idEvento == BOTON_EINT2_ALARM){
				botones_monitorizar(idEvento);
				
			}else if(idEvento == DEEP_SLEEP){
				power_hal_deep_sleep();
			}
			else if(idEvento == ev_VISUALIZAR_CUENTA){
				visualizarCuenta(auxData);
			}
			else if(idEvento == ev_LATIDO){
				hello_world_tratar_evento();
			}
			else if(idEvento == ev_VISUALIZAR_HELLO){
				visualizarHello(auxData);
			}else if(idEvento == ev_TEST){
				//printf("Test completado %d", auxData);
				if(auxData == 1){
					testAlarmas2();
				}else if(auxData == 2){
					
					if(FIFO_estadisticas(ev_TEST) == 5){
						//quitar alarma periodica
						alarma_activar(ev_TEST,0,0);
						alarma_activar(TEST_OK,200,0);
						
					}else if(FIFO_estadisticas(ev_TEST)==6){
						FIFO_encolar(ALARMA_OVERFLOW,0);
					}
				}
			}else if(idEvento == TEST_OK){
					testAlarmasOverflow();
			}
		}else{
			power_hal_wait();
					
		}
       
    }
}
