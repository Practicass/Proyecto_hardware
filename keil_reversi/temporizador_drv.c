


#include "temporizador_drv.h"
void (*funcion_callback1)();
uint8_t event;


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

void funcion_auxiliar(){
	funcion_callback1(event);
}


void temporizador_drv_reloj(uint32_t periodo, void
(*funcion_encolar_evento)(), EVENTO_T ID_evento){
		event = ID_evento;
		funcion_callback1 = funcion_encolar_evento;
    temporizador_hal_reloj(periodo,funcion_auxiliar);

}

