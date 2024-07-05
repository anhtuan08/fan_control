/*
 * UART.h
 *
 *  Created on: Jun 28, 2024
 *      Author: ASUS
 */

#ifndef UART_H_
#define UART_H_

#define BAUDRATE 9600
#define UART_COMMAND_STRING 14
#define LENGTH 14
#define MIN_LENGTH 0

#define start_bit 1
#define stop_bit 13

#define length_bit 7
#define id_bit 4

#define mode_bit 10

#include "led.h"
#include "PWM.h"


void configUART();

void sendString(uint8_t *string);

void sendChar(uint8_t data);

void return_default();

uint8_t check_length(uint8_t data);

void check_id_bit(uint32_t* data);

uint8_t check_buff_0(uint32_t *data, uint8_t length);

uint8_t check_start_bit(uint32_t *data);

uint8_t check_mode(uint32_t* data);

#endif /* UART_H_ */
