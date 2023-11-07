#include "planificador_test_alarmas.h"


void planificadorTestAlarmas(){
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
	
	testAlarmas1(); // descomentar para que se lanza el primer test de alarmas
	
    //Bucle infinito pendiente de eventos 
    while(idEvento != ALARMA_OVERFLOW){
			//uint8_t hayEvento = 0; //descomentar comprobar overflow cola
    	uint8_t hayEvento =  FIFO_extraer(&idEvento, &auxData); //comentar para comprobar overflow cola
			
    	if (hayEvento != 0) {
                if(idEvento == ALARMA_OVERFLOW){
						gpio_hal_escribir( GPIO_OVERFLOW, GPIO_OVERFLOW_BITS,  GPIO_HAL_PIN_DIR_OUTPUT);
				}else if(idEvento == TIMER){
					alarma_tratar_evento();
				}else if(idEvento == ev_TEST){
					if(auxData == 1){ // si el test1 se ha completado correctamente entrar� a este if y se lanza el test2
						testAlarmas2();
					}else if(auxData == 2){ // si el test2 se ha completado correctamente entrar� a este if
						if(FIFO_estadisticas(ev_TEST) == 5){
						
							alarma_activar(ev_TEST,0,0); 	//quitamos la alarma periodica y comprobamos que se eliminan correctamente las alarmas
							alarma_activar(TEST_OK,200,0);	// se programa una alarma com mayor periodo que la peridoica para comprobar que se ha eliminado
						}else if(FIFO_estadisticas(ev_TEST)==6){ // si no se elimina correctamente la alarma peri�dicaentrar� a este if y se encender� el pin OVERFLOW
							FIFO_encolar(ALARMA_OVERFLOW,0); 
						}
					}
				}else if(idEvento == TEST_OK){ // si la alarma se ha elimnado correctamente se encolar� unicamente el evento de tipo TEST_OK								
						testAlarmasOverflow(); //y se lanzar� el �ltimo test que comprueba que no se puedan crear m�s alarmas de las posibles
				}
		}else{
			power_hal_wait();
					
		}
       
    }
}
