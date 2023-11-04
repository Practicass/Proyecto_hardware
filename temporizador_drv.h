

#ifndef TEMPORIZADOR_DRV_H
#define TEMPORIZADOR_DRV_H


#include "temporizador_hal.h"

#include "fifo.h"


//función que programa un contador para que pueda ser utilizado.
void temporizador_drv_iniciar(void);

//función que inicia la cuenta de un contador de forma indefinida
void temporizador_drv_empezar(void);

//función que lee el tiempo que lleva contando el contador desde la 
//última vez que se ejecutó temporizador_drv_empezar y lo devuelve 
//en microsegundos.
uint64_t temporizador_drv_leer(void);

//detiene el contador y devuelve el
//tiempo transcurrido desde el último temporizador_drv_empezar
uint64_t temporizador_drv_parar(void); 


//función que programa el reloj para que encole un evento periódicamente 
//en la cola del planificador. El periodo se indica en ms
void temporizador_drv_reloj(uint32_t periodo, void
(*funcion_encolar_evento)(), EVENTO_T ID_evento);

#endif
