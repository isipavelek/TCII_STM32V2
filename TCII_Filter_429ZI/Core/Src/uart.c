/*
 * UART.c
 *
 *  Created on: Jun 4, 2024
 *      Author: ipave
 */

#include <stdint.h>
#include "uart_port.h"
#include "filter.h"
#include "uart.h"

uint8_t RxChar3;
extern filter_type_t filter; //Función que ejecuta
const uint8_t txt1[]="Menu:\r\n";
const uint8_t txt2[]="Ingrese 1 para TALKTHROUGHr\n\r";
const uint8_t txt3[]="Ingrese 2 para FIR\n\r";
const uint8_t txt4[]="Ingrese 3 para IIR\n\r";
const uint8_t txt5[]="Ingrese 4 nada\n\r";
extern float32_t OutputA[SAMPLES_PER_BLOCK];
extern float32_t OutputB[SAMPLES_PER_BLOCK];

void UART_handler(void){
	if(RxChar3=='1'){
		filter= TALKTHROUGH;
		UART_Transmit((const uint8_t *)"TALKTHROUGH\r\n", sizeof("TALKTHROUGH\r\n"));
	}else if(RxChar3=='2'){
		filter= FIR;
		UART_Transmit((const uint8_t *)"FIR\r\n", sizeof("FIR\r\n"));
	}else if(RxChar3=='3'){
		filter= IIR;
		UART_Transmit((const uint8_t *)"IIR\r\n", sizeof("IIR\r\n"));
	}else if(RxChar3=='4'){
		filter= NOTHING;
		UART_Transmit((const uint8_t *)"Nada\r\n", sizeof("Nada\r\n"));
		for(uint16_t i=0;i<SAMPLES_PER_BLOCK;i++){
			OutputA[i]=0;
			OutputB[i]=0;
		}
	}
	UART_Menu();
}
void UART_Menu(void){
	UART_Transmit(txt1, sizeof(txt1));
	UART_Transmit(txt2, sizeof(txt2));
	UART_Transmit(txt3, sizeof(txt3));
	UART_Transmit(txt4, sizeof(txt4));
	UART_Transmit(txt5, sizeof(txt5));


}
