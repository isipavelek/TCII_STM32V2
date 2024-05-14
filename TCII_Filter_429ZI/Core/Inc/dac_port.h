/*
 * dac_port.h
 *
 *  Created on: May 13, 2024
 *      Author: ipave
 */

#ifndef INC_DAC_PORT_H_
#define INC_DAC_PORT_H_

extern DAC_HandleTypeDef hdac;

void DAC_Init(void);
void DAC_Write(uint32_t value);

#endif /* INC_DAC_PORT_H_ */
