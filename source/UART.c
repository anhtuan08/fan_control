#include "UART.h"


void configUART(){
	//Enable UART0 mode
	SIM->SCGC4 |= (1 << 10);
	SIM->SOPT2 |= (1 << 26); //MCGDPLL / 2

	//Config portA for UART0
	SIM->SCGC5 |= (1 << 9);
	//PAT1 = rx, PTA2 = TX
	PORTA->PCR[1] |= (2 << 8);
	PORTA->PCR[2] |= (2 << 8);

	//Config baudrate
	uint32_t sbr = (SystemCoreClock/(16 * BAUDRATE));
	UART0->BDH = sbr >> 8;
	UART0->BDL = sbr;

	//Config 8 or 9 bit tranmission
	UART0->C1 &= ~(1 << 4);
	//No parity bit
	UART0->C1 &= ~(1 << 1);
	//One stop bit
	UART0->BDH &= ~(1 << 5);

	//Enable Te, RE
	UART0->C2 |= (1 << 2) | (1 <<3);

	//
	UART0->C2 |= (1 << 5);
	NVIC_ClearPendingIRQ(12);
	NVIC_EnableIRQ(12);
}

void sendChar(uint8_t data){
	while(!(UART0->S1 & (1 << 7)));
		UART0->D = data;
}

void sendString(uint8_t* string){
	while(*string){
		sendChar(*string);
		string++;
	}
}

void return_default(){
	static uint8_t flag = 0;
	if(!flag){
		sendString("0x02 0xff 0x01 0xff 0x03");
		flag = 1;
	}
}

uint8_t check_length(uint8_t data){
	uint8_t check = 0;
	if(data < 15){
		check++;
	}
	return check;
}

void check_id_bit(uint32_t* data){
	switch(data[id_bit]){
	case '0':
		configPWM_0();
		break;
	case '1':
		configPWM_30();
		break;
	case '2':
		configPWM_60();
		break;
	case '3':
		configPWM_90();
		break;
	default:
		return_default();
		break;
	}
}

uint8_t check_buff_0(uint32_t *data, uint8_t length){
	uint8_t i = 0;
	uint8_t count = 0;
	for(i = 0; i < length; i++){
		if(i % 3 == 0){
			if(data[i] == '0'){
				//check START
				count++;
			}
		}
	}
	return count;
}

uint8_t check_start_bit(uint32_t *data){
	uint8_t count = 0;
	if(data[start_bit] == '2' && data[stop_bit] == '3' && data[length_bit] == '1'){
		count = 1;
	}
	return count;
}

uint8_t check_mode(uint32_t* data){
	uint8_t count = 0;
		if(data[mode_bit] == '1'){
			count = 1;
		}
		else if(data[mode_bit] == '2'){
			count = 2;
		}
		return count;
}

