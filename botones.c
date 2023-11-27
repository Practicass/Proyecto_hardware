


#include "botones.h"

enum ESTADO boton_1, boton_2 ;
void (*funcion_callbackAlarmas)();

void botones_init(void (*funcion_callbackBotonesParam)(), void (*funcion_callbackAlarmasParam2)()){
	boton_1 = NO_PULSADO;
	boton_2 = NO_PULSADO;
	eint1_init(funcion_callbackBotonesParam);
	eint2_init(funcion_callbackBotonesParam);
	funcion_callbackAlarmas = funcion_callbackAlarmasParam2;
	
}

void botones_pulsar(uint32_t auxData){

	switch (auxData) {
		case 1:
			boton_1 = PULSADO;
			funcion_callbackAlarmas(BOTON_EINT1_ALARM,0x80000064,0);
			break;
		case 2:
			boton_2 = PULSADO;
			funcion_callbackAlarmas(BOTON_EINT2_ALARM,0x80000064,0);
			break;
	}
}

void botones_monitorizar(uint8_t ID_evento){
	
	switch (ID_evento) {
		case BOTON_EINT1_ALARM:
			if(!eint1_hold()){
				funcion_callbackAlarmas(BOTON_EINT1_ALARM, 0,0);
				boton_1 = NO_PULSADO;
				eint1_enable();
			}
			
			break;
		case BOTON_EINT2_ALARM:
			if(!eint2_hold()){
				funcion_callbackAlarmas(BOTON_EINT2_ALARM, 0,0);
				boton_1 = NO_PULSADO;
				eint2_enable();
			}

			break;
	}
}





