
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <inttypes.h>

#include "gpio_hal.h"
#include "temporizador_drv.h"
#include <math.h>



typedef void* funciontype;


//actualiza el contador y el estado de los leds 
void hello_world_tick_tack(void);

//configura los pines correspondientes
void hello_world_inicializar(GPIO_HAL_PIN_T gpio_inicial, uint8_t num_bits,  enum gpio_hal_pin_dir_t direccion);


#endif
