
#include "hello_world.h"


funciontype func = &FIFO_encolar;
uint32_t x;

//actualiza el contador y el estado de los leds 
void hello_world_tick_tack(){

		//aumenta el contador
    x= x+1;
		if(x >= pow(2,GPIO_HELLO_WORLD_BITS)){
			x=1;
		}
			
		
		
}

//configura los pines correspondientes
void hello_world_inicializar(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits,  enum gpio_hal_pin_dir_t direccion){
	uint32_t periodo;	
	x=1;
		
	
		
	
		//configurar direccion de los pines
    gpio_hal_sentido(gpio_inicial, num_bits, direccion);

		//prgramar el reloj para que encole evento cada periodo ms
		periodo= 0x8000000a;
		
    //temporizador_drv_reloj(periodo, func, ev_LATIDO);
	alarma_activar(ev_LATIDO,periodo,0);
		//llamar a alarma
     
    
}


void hello_world_tratar_evento(){
	
	hello_world_tick_tack(); // aumenta el contador
	FIFO_encolar(ev_VISUALIZAR_HELLO,x); // encola el evento para visualizar y el valor a visualizar
}
