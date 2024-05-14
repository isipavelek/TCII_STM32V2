/*
 * adc_port.c
 *
 *  Created on: Oct 3, 2023
 *      Author: ipave
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "adc_port.h"

void ADC_Init(void){
	HAL_ADC_Start_IT(&hadc1);

	HAL_TIM_Base_Start(&htim2);
}
uint32_t ADC_Read(){
	return (HAL_ADC_GetValue(&hadc1));
}
