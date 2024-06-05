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


estado_t estado=NO_PROCESAR;

extern float32_t InputA[SAMPLES_PER_BLOCK];
extern float32_t InputB[SAMPLES_PER_BLOCK];
extern float32_t OutputA[SAMPLES_PER_BLOCK];
extern float32_t OutputB[SAMPLES_PER_BLOCK];



#define CARGANDO_A false


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	static bool estadoADC = CARGANDO_A;
	static uint16_t index = 0;
	uint32_t val=ADC_Read();
	if (estadoADC==CARGANDO_A){
		InputA[index] =(float32_t)val;
		DAC_Write((uint32_t)OutputA[index]);
	}
	else {
		InputB[index] =(float32_t) val ;
		DAC_Write((uint32_t)OutputB[index]);
	}

	index++;
	if (index == SAMPLES_PER_BLOCK) {
		index = 0;
		if(estadoADC==CARGANDO_A)estado=PROCESAR_A;
		else estado=PROCESAR_B;
		estadoADC ^= 1;
	}
	HAL_GPIO_TogglePin(MEASURE_Pin_GPIO_Port,MEASURE_Pin);

}
