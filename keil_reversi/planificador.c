
#include "planificador.h"





void planificador(){
    EVENTO_T idEvento;
		uint32_t auxData;
		
	
	// inicializar gpio
    gpio_hal_iniciar();
    //Inicializar la cola 
	
    FIFO_inicializar(GPIO_OVERFLOW);
	alarma_inicializar(FIFO_encolar);
	hello_world_inicializar(GPIO_HELLO_WORLD, GPIO_HELLO_WORLD_BITS, GPIO_HAL_PIN_DIR_OUTPUT,FIFO_encolar);

	botones_init(FIFO_encolar,alarma_activar);
	juego_inicializar(FIFO_encolar)
    
	visualizarInicializar();

	ls_inicializar(FIFO_encolar, ev_RX_SERIE,UART0_CARACTER,CONTINUAR_ENVIO,ev_TX_SERIE);
	

		
	//alarma_activar(HELLOWORLD, 0x8000000a,0);
    //Bucle infinito pendiente de eventos 
	//alarma_activar(DEEP_SLEEP, USUARIO_AUSENTE, 0);

	
    while(idEvento != ALARMA_OVERFLOW){
			//uint8_t hayEvento = 0; //descomentar comprobar overflow cola
    	uint8_t hayEvento =  FIFO_extraer(&idEvento, &auxData); //comentar para comprobar overflow cola
			
    	if (hayEvento != 0) {
				if(idEvento == HELLOWORLD){
					hello_world_tick_tack();
				}else if(idEvento == ALARMA_OVERFLOW){
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
				}else if(idEvento == ev_VISUALIZAR_CUENTA){
					visualizarCuenta(auxData);
				}else if(idEvento == ev_LATIDO){
					hello_world_tratar_evento();
				}else if(idEvento == ev_VISUALIZAR_HELLO){
					visualizarHello(auxData);
				}else if(idEvento == ev_RX_SERIE){
					linea_serie_drv_enviar_array(auxData);
					//if (auxData == "TAB"){
					//	juego_tratar_evento(idEvento,auxData);
					//}
				}else if(idEvento  == UART0_CARACTER){
					linea_serie_hal(auxData);
				}else if(idEvento  == CONTINUAR_ENVIO){
					linea_serie_drv_continuar_envio();
				}else if(idEvento  == ev_TX_SERIE){
					idEvento = idEvento;
				}
		}else{
			power_hal_wait();
					
		}
       
    }
}
