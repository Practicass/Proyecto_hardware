
#include "hello_world.h"


funciontype func = &FIFO_encolar;
uint32_t x;

//actualiza el contador y el estado de los leds 
void hello_world_tick_tack(){
	
		//activa los pines
    gpio_hal_escribir(GPIO_HELLO_WORLD,GPIO_HELLO_WORLD_BITS, x);
		//aumenta el contador
    x= x*2;
		if(x >= pow(2,GPIO_HELLO_WORLD_BITS)){
			x=1;
		}
			
		
		
}

//configura los pines correspondientes
void hello_world_inicializar(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits,  enum gpio_hal_pin_dir_t direccion){
	uint32_t periodo;	
	x=1;
		
	
		// inicializar gpio
    gpio_hal_iniciar();
	
		//configurar direccion de los pines
    gpio_hal_sentido(gpio_inicial, num_bits, direccion);

		//prgramar el reloj para que encole evento cada periodo ms
		periodo= 10;
		
    //temporizador_drv_reloj(periodo, func, HELLOWORLD);
		//llamar a alarma
     
    
}
