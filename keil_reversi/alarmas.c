#include "alarmas.h"

struct alarm alarmas[ALARMAS_MAX];


int indexAlarms[NUMEVENTOS];

static void (*funcion_callbackAlarmas)();

void alarma_inicializar(void (*funcion_callbackAlarmasParam)()){

    int i = 0;
    while (i<= ALARMAS_MAX)
    {   
        //inicializar los registros
        alarmas[i].contador = 0;
        alarmas[i].periodica = 0;
        alarmas[i].ocupado = 0;
        alarmas[i].evento = 0;
        alarmas[i].auxdata = 0;
				i++;
    }
    i = 0;
    while (i <NUMEVENTOS)
    {
        indexAlarms[i] = -1; //-1 indica que no existe alamra de ese evento
				i++;
    }
		temporizador_drv_reloj(1, funcion_callbackAlarmasParam, TIMER);
        funcion_callbackAlarmas = funcion_callbackAlarmasParam;
    
    
}

void alarma_activar(EVENTO_T ID_evento, uint32_t retardo, uint32_t
auxData){
    int i = 0;
    int periodico;
    int retardoAux;
    int id;

    
    if(retardo == 0){ 
        
        //se quita la alarma correspondiente de ese evento del vector de alarmas
        id = indexAlarms[ID_evento];
        indexAlarms[ID_evento] = -1;

        //se reseta la alarma
        alarmas[id].contador = 0;
        alarmas[id].periodica = 0;
        alarmas[id].ocupado = 0;
        alarmas[id].evento = 0;
        alarmas[id].auxdata = 0;

    }else{
        //comprobar si alarma periódica, bit de más peso retardo
        periodico = retardo & 0x80000000;
        retardoAux = retardo & 0x7fffffff;
        //comprobacion de la existencia de una alarma para ID_evento
        if(indexAlarms[ID_evento] == -1){ //no existe alarma para ese evento
            while(i<ALARMAS_MAX){
                if(alarmas[i].ocupado == 0){
                    alarmas[i].evento = ID_evento;
                    indexAlarms[ID_evento] = i;
                    alarmas[i].auxdata = auxData;
                    alarmas[i].ocupado = 1;
                    

                    // if (periodico == 0)
                    // {
                    //     alarmas[i].periodica =  0

                    // }else{

                    //     alarmas[i].periodica
                    // }
                    alarmas[i].periodica = (periodico != 0);
                    alarmas[i].periodo = retardoAux;
									
										i = ALARMAS_MAX +1;
                }

                i++;
            }
            if (i == ALARMAS_MAX) //no hay alarmas disponibles
            {
                //generar evento ALARMA_OVERFLOW
                funcion_callbackAlarmas(ALARMA_OVERFLOW, 0);
            }
            
        }else{ //existe alarma para ese evento
            id = indexAlarms[ID_evento];
            alarmas[id].contador = 0;
            alarmas[id].auxdata = auxData;
            alarmas[id].periodica = (periodico != 0);
            alarmas[id].periodo = retardoAux;
        }
    }


}


void alarma_tratar_evento(void){
    int i = 0;
		int id;
    while(i<ALARMAS_MAX){
        if(alarmas[i].ocupado == 1){ //existe alarma
            alarmas[i].contador++ ;
            if(alarmas[i].contador >= alarmas[i].periodo){ //expira alarma
                funcion_callbackAlarmas(alarmas[i].evento, alarmas[i].auxdata);
                if(alarmas[i].periodica == 0){ //se debe repetir 
                    //se quita la alarma correspondiente de ese evento del vector de alarmas
                    id = alarmas[i].evento;
                    indexAlarms[id] = -1;

                    //se reseta la alarma
                    alarmas[i].contador = 0;
                    alarmas[i].periodica = 0;
                    alarmas[i].ocupado = 0;
                    alarmas[i].auxdata = 0;
                    alarmas[i].evento = 0;
                }else{
                    alarmas[i].contador = 0;
                }
            }
        }
				i++;
    }
}
