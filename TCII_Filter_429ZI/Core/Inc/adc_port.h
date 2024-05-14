/*
 * adc_port.h
 *
 *  Created on: Oct 3, 2023
 *      Author: ipave
 */

#ifndef INC_ADC_PORT_H_
#define INC_ADC_PORT_H_

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;

void ADC_Init(void);
uint32_t ADC_Read();

#endif /* INC_ADC_PORT_H_ */
