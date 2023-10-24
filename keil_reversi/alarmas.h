
#include "fifo.h"

#define ALARMAS_MAX 4

void alarma_inicializar(void);

void alarma_activar(EVENTO_T ID_evento, uint32_t retardo, uint32_t
auxData);

void alarma_tratar_evento(void);