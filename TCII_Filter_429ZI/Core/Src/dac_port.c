/*
 * dac_port.c
 *
 *  Created on: May 13, 2024
 *      Author: ipave
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "dac_port.h"

void DAC_Init(void){

	HAL_DAC_Start(&hdac,DAC_CHANNEL_1);

}

void DAC_Write(uint32_t value){
	HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R, value);
}
