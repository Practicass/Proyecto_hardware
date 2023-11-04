
#ifndef BOTONES
#define BOTONES

#include "int_externas_hal.h"
#include "alarmas.h"
#include "gpio_hal.h"

enum ESTADO{
    PULSADO,
    NO_PULSADO
};


void botones_init(void);

void botones_pulsar(uint32_t auxData);

void botones_monitorizar(uint8_t ID_evento);




#endif



