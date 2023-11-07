
#include "test.h"



void testAlarmas(){
    testAlarmas1();  
    testAlarmas2();
    testAlarmasOverflow();
}

//test que comprueba la programación de una alarma
void testAlarmas1(void){
	//programar una alarma 
    alarma_activar(ev_TEST, 100, 1);
    
}


//test que comprueba la programación de alarmas periódicas
void testAlarmas2(void){
    //programar una alarma periodica
    alarma_activar(ev_TEST, 0x80000064, 2);
}


//test que comprueba el limite de alarmas simultaneas
void testAlarmasOverflow(void){
	//programar nas de cuatro alarmas
    alarma_activar(ev_TEST, 100, 0);
    alarma_activar(VOID, 100, 0);
    alarma_activar(BOTON, 100, 0);
    alarma_activar(BOTON_EINT1_ALARM, 100, 0);
    alarma_activar(BOTON_EINT2_ALARM, 100, 0);
}








