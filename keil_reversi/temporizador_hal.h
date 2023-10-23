
#ifndef TEMPORIZADOR_HAL_H
#define TEMPORIZADOR_HAL_H

#define TEMPORIZADOR_HAL_TICKS2US  3000

#include <inttypes.h>




void temporizador_hal_iniciar(void);
void temporizador_hal_empezar(void);

uint64_t temporizador_hal_leer(void);

uint64_t temporizador_hal_parar(void);

void temporizador_hal_reloj (uint32_t periodo, void
(*funcion_callback)());





#endif

