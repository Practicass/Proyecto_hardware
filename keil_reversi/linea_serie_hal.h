
#ifndef LINEA_SERIE_HAL_H
#define LINEA_SERIE_HAL_H

#include <LPC210X.H>
#include <inttypes.h>




void linea_serie_ISR(void) __irq;

void linea_serie_inicializar(void (*funcion_callback)(), void (*funcion_callback2)(), uint8_t idEvento);

void linea_serie_hal(uint8_t caracter);

#endif

