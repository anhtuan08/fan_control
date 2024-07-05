#include "PWM.h"

void configPWM(){
	//Enable TPM
	SIM->SCGC6 |= (1 << 24);

	SIM->SCGC5 |= (1 << 12);

	//config PORT_PCR -> ALterner 04
	PORTD->PCR[5] |= (4 << 8);

	SIM->SOPT2 |= (1 << 24);

	//
	TPM0->SC |= (1 << 3);

	TPM0->MOD = SystemCoreClock - 1;

	TPM0->CONTROLS[5].CnSC |= (1 << 5) | (1 << 3);
}

void configPWM_90(){
		TPM0->CONTROLS[5].CnV = 6553;
}

void configPWM_60(){
		TPM0->CONTROLS[5].CnV = 26214;
}

void configPWM_30(){
		TPM0->CONTROLS[5].CnV = 45874;
}

void configPWM_0(){
		TPM0->CONTROLS[5].CnV = 65535;
}

