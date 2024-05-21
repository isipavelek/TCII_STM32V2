/*
 * adc.c
 *
 *  Created on: Oct 3, 2023
 *      Author: ipave
 */


#include<stdio.h>
#include <stdbool.h>
#include "arm_math.h"
#include "adc.h"
#include "filter.h"
#include "dac_port.h"


uint8_t estado = 0;
procesar_type_t procesar=NO_PROCESAR;

extern float32_t InputA[SAMPLES_PER_BLOCK];
extern float32_t InputB[SAMPLES_PER_BLOCK];
extern float32_t OutputA[SAMPLES_PER_BLOCK];
extern float32_t OutputB[SAMPLES_PER_BLOCK];

#define CARGANDO_A false




void HAL_ADC_ConCpltCallback(ADC_HandleTypeDef* hadc){
	static uint16_t index = 0;
	uint32_t val=ADC_Read();
	if (estado==CARGANDO_A){
		InputA[index] =(float32_t) val;
		DAC_Write((uint32_t)OutputA[index]);
	}
	else {
		InputB[index] =(float32_t) val ;
		DAC_Write((uint32_t)OutputB[index]);
	}

	index++;
	if (index == SAMPLES_PER_BLOCK) {
		index = 0;
		if(estado==CARGANDO_A)procesar=PROCESAR_A;
		else procesar=PROCESAR_B;
		estado ^= 1;
	}
}
