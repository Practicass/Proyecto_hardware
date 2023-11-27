#ifndef LINEA_SERIE_DRV_H
#define LINEA_SERIE_DRV_H

#include "linea_serie_hal.h"

#include "gpio_hal.h"
#include "SWI.h"



void ls_inicializar(void (*funcion_callback4)(), uint8_t idEvento, uint8_t idEvento2, uint8_t idEvento3, uint8_t idEvento4);

void ls_leer_caracter(uint8_t caracter);

void linea_serie_drv_enviar_array(uint32_t comando);

void linea_serie_drv_continuar_envio(void);

#endif

