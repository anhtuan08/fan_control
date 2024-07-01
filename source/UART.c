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

void sendString(uint8_t *string){
	while(*string){
		sendChar(*string);
		string++;
	}
}



