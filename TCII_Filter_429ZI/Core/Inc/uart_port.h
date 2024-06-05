/*
 * uart_port.h
 *
 *  Created on: Jun 4, 2024
 *      Author: ipave
 */

#ifndef INC_UART_PORT_H_
#define INC_UART_PORT_H_

void UART_Transmit(const uint8_t *, uint16_t );
void UART_Receive_IT_init(void);

#endif /* INC_UART_PORT_H_ */
