


#include "temporizador_drv.h"
#include "temporizador_hal.h"


void temporizador_drv_iniciar(void){
    temporizador_hal_iniciar();
}
void temporizador_drv_empezar(void){
    temporizador_hal_empezar();
}
uint64_t temporizador_drv_leer(void){
	uint64_t aux = temporizador_hal_leer() / TEMPORIZADOR_HAL_TICKS2US;
    return aux;
}
uint64_t temporizador_drv_parar(void){
    uint64_t aux = temporizador_hal_parar() /TEMPORIZADOR_HAL_TICKS2US;
    return aux;
}
