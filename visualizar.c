

#include "visualizar.h"

void visualizarInicializar(void ){
    gpio_hal_sentido(16,8,GPIO_HAL_PIN_DIR_OUTPUT);
}

void visualizarCuenta(uint32_t cuenta){
    gpio_hal_escribir(16,8,cuenta);
}

void visualizarHello(uint32_t led){
    gpio_hal_escribir(GPIO_HELLO_WORLD,GPIO_HELLO_WORLD_BITS, led);
}


