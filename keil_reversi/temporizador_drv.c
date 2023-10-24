


#include "temporizador_drv.h"
void (*funcion_callback1)();
uint8_t event;

//función que programa un contador para que pueda ser utilizado.
void temporizador_drv_iniciar(void){
    temporizador_hal_iniciar();
}

//función que inicia la cuenta de un contador de forma indefinida
void temporizador_drv_empezar(void){
    temporizador_hal_empezar();
}

//función que lee el tiempo que lleva contando el contador desde la 
//última vez que se ejecutó temporizador_drv_empezar y lo devuelve 
//en microsegundos.
uint64_t temporizador_drv_leer(void){
	uint64_t aux = temporizador_hal_leer() / TEMPORIZADOR_HAL_TICKS2US;
    return aux;
}

//detiene el contador y devuelve el
//tiempo transcurrido desde el último temporizador_drv_empezar
uint64_t temporizador_drv_parar(void){
    uint64_t aux = temporizador_hal_parar() /TEMPORIZADOR_HAL_TICKS2US;
    return aux;
}


void funcion_auxiliar(){
	funcion_callback1(event);
}

//función que programa el reloj para que encole un evento periódicamente 
//en la cola del planificador. El periodo se indica en ms
void temporizador_drv_reloj(uint32_t periodo, void
(*funcion_encolar_evento)(), EVENTO_T ID_evento){
		event = ID_evento;
		funcion_callback1 = funcion_encolar_evento;
    temporizador_hal_reloj(periodo,funcion_auxiliar);

}

