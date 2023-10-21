#include "fifo.h"

struct fifo
{
    EVENTOS queue[TAM];
    int index_begin, index_end;
    GPIO_HAL_PIN_T pin_overflow;

};

struct fifo cola;
//Inicialización de la cola. Se le pasa como parámetro el pin del GPIO utilizado para marcar errores.
void FIFO_inicializar(GPIO_HAL_PIN_T pin_overflow){
    cola.index_begin = -1;
    cola.index_end = -1;
    cola.pin_overflow = pin_overflow;

}

//Esta función guardará en la cola el evento. El campo ID_evento, que permita identificar el evento (p.e. qué interrupción ha saltado) 
//y el campo auxData en caso de que el evento necesite pasar información extra.
void FIFO_encolar(EVENTO_T ID_evento, uint32_t auxData){

    cola.index_end = (cola.index_end +1) % TAM;
    cola.queue[cola.index_end].id = ID_evento;
    cola.queue[cola.index_end].auxData = auxData;
}

//Si hay eventos sin procesar, devuelve un valor distinto de cero y el evento más antiguo sin procesar por referencia. Cero indicará 
//que la cola está vacía y no se ha devuelto ningún evento.
uint8_t FIFO_extraer(EVENTO_T *ID_evento, uint32_t* auxData){
    if(cola.index_begin != cola.index_end ){

        ID_evento = &(cola.queue[cola.index_begin].id);
        auxData = &(cola.queue[cola.index_begin].auxData);
        cola.index_begin = (cola.index_begin +1) % TAM;
        return 1;
    }else{
        return 0;
    }
}

//Dado un identificador de evento nos devuelve el número total de veces que ese evento se ha encolado. El evento VOID nos devolverá 
//el total de eventos encolados desde el inicio.
uint32_t FIFO_estadisticas(EVENTO_T ID_evento){
    uint32_t cont = 0;
   
    int i = 0;
    while (i < TAM)
    {
        if (cola.queue[i].id == ID_evento ){
            cont= cont +1;
        }
         i=i+1;
    }
    
    return cont;
}



