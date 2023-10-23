#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#include <LPC210X.H>
#include <inttypes.h>
#include "io_reserva.h"

	
typedef uint8_t GPIO_HAL_PIN_T;

enum  gpio_hal_pin_dir_t{
	GPIO_HAL_PIN_DIR_INPUT,
	GPIO_HAL_PIN_DIR_OUTPUT
};





__inline static
void gpio_hal_iniciar(){

    PINSEL0 = 0;
    PINSEL1 = 0;

}


__inline static void 
gpio_hal_sentido( GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits,  enum gpio_hal_pin_dir_t direccion){
	
    if(direccion == GPIO_HAL_PIN_DIR_OUTPUT){
	    IODIR = IODIR | (~(0xFFFFFFFF << num_bits) << gpio_inicial);
    }else{
	    IODIR = IODIR &  (~(~(0xFFFFFFFF << num_bits) << gpio_inicial));
        
    }
}


__inline static uint32_t
gpio_hal_leer( GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits){
	
	return gpio_inicial >> (IOPIN & (~(0xFFFFFFFF << num_bits) << gpio_inicial));
	
}


__inline static void 
gpio_hal_escribir( GPIO_HAL_PIN_T bit_inicial, uint8_t num_bits, uint32_t valor){

		IOSET = valor << bit_inicial & ((~(0xFFFFFFFF << num_bits)) << bit_inicial);	
		IOCLR = ~valor << bit_inicial  & ((~(0xFFFFFFFF << num_bits)) << bit_inicial);
		
}

#endif
