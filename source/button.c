#include "button.h"

void initButton(){
	//PORTC
	SIM->SCGC5 |= (1 << 11);

	PORTC->PCR[3] |= (1 << 8);

	PORTC->PCR[3] |= (1 << 0) | (1 << 1);

	//Enable IRQC
	PORTC->PCR[3] |= (10 << 16); //Interupt when falling edge - press

}

void statusButton(){

		NVIC_ClearPendingIRQ(31);
		NVIC_EnableIRQ(31);
	}



void check_count(int level) {
    switch (level) {
        case 0:
            configPWM_0(); // 0% brightness
            break;
        case 1:
        	configPWM_30(); // 25% brightness
            break;
        case 2:
        	configPWM_60(); // 50% brightness
            break;
        case 3:
        	configPWM_90(); // 75% brightness
            break;
        default:
        	configPWM_0(); // Default to 0% brightness
            break;
    }
}



