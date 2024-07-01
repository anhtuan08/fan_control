#include "led.h"

void turn_on_red_led(){

	//Red Led
	SIM->SCGC5 |= (1 << 13);

	PORTE->PCR[29] |= 1 << 8;

	PTE-> PDDR |= 1 << 29;

}

void turn_off_red_led(){
	PTE->PSOR |= 1 << 29;

}
