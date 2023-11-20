
#ifndef WD_HAL_H
#define WD_HAL_H

#include <LPC210X.H>  
#include "SWI.h"

void WD_hal_inicializar(int sec);
void WD_hal_feed(void);
void WD_hal_test(void);

#endif

