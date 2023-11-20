

#include "linea_serie_drv.h"


int num = 0;
int almacenar = 0;
const int MAXBUFFER = 3;
const int MAXBUFFERSALIDA = 3;
void (*funcion_callback3)();
uint8_t evento;
uint8_t evento2;
uint8_t evento3;
uint8_t evento4;
uint8_t bufferSalida[MAXBUFFERSALIDA];
int i = 1; 

uint8_t buffer[MAXBUFFER];

void ls_inicializar(void (*funcion_callback4)(), uint8_t idEvento, uint8_t idEvento2, uint8_t idEvento3, uint8_t idEvento4){
    funcion_callback3 = funcion_callback4;
		evento = idEvento;
        evento2 = idEvento2;
        evento3 = idEvento3;
        evento4 = idEvento4;
    gpio_hal_sentido(GPIO_SERIE_ERROR, GPIO_SERIE_ERROR_BITS, GPIO_HAL_PIN_DIR_OUTPUT);
    linea_serie_inicializar(&ls_leer_caracter,funcion_callback3,idEvento3);
}

void ls_leer_caracter(uint8_t caracter){
    if(caracter == '$'){ // comenzará a almacenar en la siguiente interrupción
        almacenar = 1;
        num = 0;
        if(gpio_hal_leer(GPIO_SERIE_ERROR, GPIO_SERIE_ERROR_BITS) == 1){
            gpio_hal_escribir(GPIO_SERIE_ERROR, GPIO_SERIE_ERROR_BITS, 0);
        }
        
    }else if(almacenar && num == 3 && caracter == '!'){ // se recibe el caracter ! y se para de alamacenar
    
        almacenar = 0;
        num = 0;
        
        if((buffer[0] == 'E' && buffer[1] == 'N'&& buffer[2] == 'D')||(buffer[0] == 'N' && buffer[1] == 'E'&& buffer[2] == 'W')||(buffer[0] == 'T' && buffer[1] == 'A'&& buffer[2] == 'B')||(buffer[0] >= '1' && buffer[1] == '-' && buffer[2] <= '7')){
            funcion_callback3(evento, (buffer[0] << 16) | (buffer[1] << 8) | buffer[2]);
        }

    }else if(num >= 3){ // se han introducio más caracteres de los posibles
        almacenar = 0;
        //encender led error
        gpio_hal_escribir(GPIO_SERIE_ERROR, GPIO_SERIE_ERROR_BITS, 1);

    }else if(almacenar){ // se almacena el caracter introducido 
        buffer[num] = caracter;
        num++;
    }
}

void linea_serie_drv_enviar_array(uint32_t cadena){
    // falta for
    // se separa la cadena entera en sus caracteres
    bufferSalida[0] = (cadena >> 16 ) & 0xFF;
    bufferSalida[1] = (cadena >> 8) & 0xFF;
    bufferSalida[2] = cadena & 0xFF;

    
    // generar evento que llame a linea_serie_hal
    funcion_callback3(evento2, bufferSalida[0]);

    // generar evento que llame a linea sereie_drv_continuar_envio, dnd se generara el evento ev_TX_SERIE
    
    

    
}

void linea_serie_drv_continuar_envio(){

    if(i < MAXBUFFERSALIDA){
        funcion_callback3(evento2, bufferSalida[i]);
        i++;
    }
    else{
        // se genera el evento ev_TX_SERIE
        funcion_callback3(evento4,0);
        i=1;
    }
    

}
