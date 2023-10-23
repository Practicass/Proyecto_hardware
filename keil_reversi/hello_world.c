
#include "hello_world.h"


funciontype func = &FIFO_encolar;
uint32_t x;

void hello_world_tick_tack(){
	
    gpio_hal_escribir(GPIO_HELLO_WORLD,GPIO_HELLO_WORLD_BITS, x);
    x= x*2;
		if(x >= pow(2,GPIO_HELLO_WORLD_BITS)){
			x=1;
		}
			
		
		
}

void hello_world_inicializar(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits,  enum gpio_hal_pin_dir_t direccion){
		x=1;
		
    gpio_hal_iniciar();
    gpio_hal_sentido(gpio_inicial, num_bits, direccion);

		
    temporizador_drv_reloj(10, func, HELLOWORLD);
     
    
}
