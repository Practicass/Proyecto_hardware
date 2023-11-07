                  
#include <LPC210x.H>                       /* LPC210x definitions */


#include "temporizador_hal.h"

#include "planificador_test_alarmas.h"




//int main (void){
//  
//  temporizador_hal_iniciar();
//  temporizador_hal_empezar();
//	while(temporizador_hal_leer() < 150){
//	}
//  temporizador_hal_empezar();
//	while(temporizador_hal_leer() < 50){
//	}
//  temporizador_hal_parar();
//
//}

//int main(void){
//	gpio_hal_iniciar();
//	gpio_hal_sentido(5,  5,  GPIO_HAL_PIN_DIR_OUTPUT);
//	//gpio_hal_sentido(6,  2,  GPIO_HAL_PIN_DIR_INPUT);
//	gpio_hal_escribir(5,4, 17); 
//	gpio_hal_escribir(5,4, 9); 
//	gpio_hal_sentido(6,  2,  GPIO_HAL_PIN_DIR_INPUT);
//}


//int i= 0;
//
//void incrementar(){
//		i++;
//}
//
//int main (void){
//	i=4;
//	temporizador_hal_reloj(10, incrementar);
//	while(i<5){
//	}
//	temporizador_hal_reloj(0,incrementar);
//	
//}

int main(void){
  
  temporizador_drv_iniciar();

  planificadorTestAlarmas();

	planificador();
  

  //se para la ejecución al saltar ALARMA_OVERFLOW y se debe reiniciar el planificador
  //planificador();


}
