#include "delay.h"


void sys_Timer(){
	//Enable Systick
	SysTick->CTRL |= (1 << 2) | (1 << 1) | (1 << 0);
	SysTick->LOAD = (SystemCoreClock/1000);

	NVIC_ClearPendingIRQ(-1);
	NVIC_EnableIRQ(-1);

}



void delay_ms(uint32_t tick){
	while(tick > msTick);
	msTick = 0;
}

