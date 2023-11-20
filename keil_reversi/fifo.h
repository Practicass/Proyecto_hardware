
#ifndef FIFO_H
#define FIFO_H
#include <inttypes.h>
#include "gpio_hal.h"
#include "SWI.h"


#define TAM 32
#define NUMEVENTOS 18

//Definici�n del tipo de datos EVENTO_T: Conjunto de eventos posibles. En el fichero de cabecera se incluir� el tipo de datos y 
//el conjunto de posibles eventos identificados con nombre humano. Reservemos el ID VOID con valor cero para inicializar la cola. 
enum ID_EVENTO
{
    VOID = 0,
    TIMER = 1,
    GPIO = 2,
    HELLOWORLD = 3,
    ALARMA_OVERFLOW = 4,
    BOTON = 5,
    BOTON_EINT1_ALARM = 6,
    BOTON_EINT2_ALARM = 7,
	DEEP_SLEEP = 8,
    ev_VISUALIZAR_CUENTA = 9,
    ev_LATIDO = 10,
    ev_VISUALIZAR_HELLO = 11,
    ev_TEST = 12,
    TEST_OK = 13,
    UART0_CARACTER = 14,
    ev_RX_SERIE = 15,
    ev_TX_SERIE = 16,
    CONTINUAR_ENVIO = 17,
};

typedef uint8_t EVENTO_T;

typedef struct EVENTOS{
    EVENTO_T id;
    uint32_t auxData;
}EVENTOS;

struct fifo{
    EVENTOS queue[TAM];
    int index_begin, index_end; // begin = eventos procesados  end= eventos encolados
    GPIO_HAL_PIN_T pin_overflow;
    int adelantado; // booleano que indica si los inidices estan adelantados o no
    uint32_t contador[NUMEVENTOS];

};



//Inicializaci�n de la cola. Se le pasa como par�metro el pin del GPIO utilizado para marcarerrores.
void FIFO_inicializar(GPIO_HAL_PIN_T pin_overflow); 

//Esta funci�n guardar� en la cola el evento. El campo ID_evento, que permita identificar el evento (p.e. qu� interrupci�n ha saltado) 
//y el campo auxData en caso de que el evento necesite pasar informaci�n extra.
void FIFO_encolar(EVENTO_T ID_evento, uint32_t auxData); 

//Si hay eventos sin procesar, devuelve un valor distinto de cero y el evento m�s antiguo sin procesar por referencia. Cero indicar� 
//que la cola est� vac�a y no se ha devuelto ning�n evento.
uint8_t FIFO_extraer(EVENTO_T *ID_evento, uint32_t* auxData);

//Dado un identificador de evento nos devuelve el n�mero total de veces que ese evento se ha encolado. El evento VOID nos devolver� 
//el total de eventos encolados desde el inicio.
uint32_t FIFO_estadisticas(EVENTO_T ID_evento);






#endif
