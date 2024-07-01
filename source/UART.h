/*
 * UART.h
 *
 *  Created on: Jun 28, 2024
 *      Author: ASUS
 */

#ifndef UART_H_
#define UART_H_

#define BAUDRATE 9600

#include "led.h"

void configUART();

void sendString(uint8_t *string);

void sendChar(uint8_t data);


#endif /* UART_H_ */
