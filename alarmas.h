#ifndef ALARMAS_H
#define ALARMAS_H


#include "fifo.h"

#define ALARMAS_MAX 4
struct alarm{
    int periodica; //booleano 1 = es peridodica 0 = no perisodica
    int contador; // numero de interrupciones desde la programacion de la alarma 
    EVENTO_T evento;
    uint32_t auxdata;
    int periodo; // numero de interrupciones hasta
    int ocupado; // ocupado = 0 NO hay una alarma activa, ocupado = 1 existe una alarma activa
};

void alarma_inicializar(void);

void alarma_activar(EVENTO_T ID_evento, uint32_t retardo, uint32_t
auxData);

void alarma_tratar_evento(void);


#endif
