
#include "juego.h"

static volatile int cuenta;
static volatile int intervalo;
static volatile int ultimaPulsacion = 0;
static volatile int primeraVez = 0;

void juego_inicializar(){
	cuenta = 0;
	intervalo = 0;
	conecta_K_jugar();
}

void juego_tratar_evento(EVENTO_T ID_evento, uint32_t auxData){
	if (ID_evento == ev_RX_SERIE){
		conecta_K_visualizar_tablero();
	}
	if (primeraVez == 0){
		primeraVez = 1;
	}else{
		uint64_t tiempo_actual;
		tiempo_actual = temporizador_drv_leer();
		intervalo = tiempo_actual - ultimaPulsacion;
		ultimaPulsacion = tiempo_actual;
	}
	
	
	if(auxData == 1){
		cuenta++;
	}else{
		cuenta--;
	}
	FIFO_encolar(ev_VISUALIZAR_CUENTA, cuenta);
	
}

void conecta_K_visualizar_tablero()
{

	
}  



void conecta_K_visualizar_tiempo(int num){

}
