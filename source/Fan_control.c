
/*
 *

Đề bài:
Thiết kế và viết chương trình điều khiển cho quạt thông qua giao thức UART với các
tính năng:
- Fan speed (PWM): Hiển thị tốc độ thông qua độ sáng của Led Green – Default
Tốc độ 0
o Level 0: 0%
o Level 1: 30%
o Level 2: 60%
o Level 3: 90%
- Mode: Hiển thị thông qua led Red – Default: UART
o UART (Led Red - Off): cho phép điều khiển tốc độ thông qua UART
 Uart command
o SW (Led Red - On): cho phép điều khiển tốc độ thông qua SW1
 Ấn 1 lần thì thay đổi tốc độ

Example:
*UART command string: 0x02 0x01 0x01 0x01 0x03* ( Start 0x02, ID 0x01, Length 0x01, Mode 0x01, Stop 0x03) => Mode UART
*UART command string: 0x02 0x01 0x01 0x02 0x03* ( Start 0x02, ID 0x01, Length 0x01, Mode 0x02, Stop 0x03) => Mode SW


Lưu ý:
*Khi gửi một chuỗi sai về ID hoặc lỗi không xác định sẽ luôn luôn gửi về là 0x02 0xff 0x01 0xff 0x03
*Khi chuyển từ điều khiển UART sang SWITCH thì trạng thái của LED sẽ luôn là 0
*Mode Fan Speed:
    - Set mode 0: 0%
    - Set mode 1: 30%
    - Set mode 2: 60%
    - Set mode 3: 90%

 * */


#include "led.h"
#include "button.h"
#include "PWM.h"
#include "UART.h"
#include "delay.h"

int count = 0;
msTick = 0;

uint8_t data = 0;

int buff[20];

void PORTC_PORTD_IRQHandler(){
		count++;
		PORTC->PCR[3] |= (1 << 24);
}


void SysTick_Handler(){
	msTick++;
}

void UART0_IRQHandler(){
	if((UART0->S1 & (1 << 5))){
		buff[data]= UART0->D;
		sendChar(buff[data]);
		data++;
//		delay_ms(2000);
	}
}

void reset_count(){
	count = 0;

}

void check_mode(uint8_t mode){
	if(mode == '1'){
		//red led on, switch mode using check count
		turn_on_red_led();
		reset_count();
		check_count(count);
	}
	else if(mode == '2'){
		turn_off_red_led();
		//using Uart mode
	}

}

void UART_mode(){

}

int main(){

	sys_Timer();
	initButton();
	statusButton();
	configPWM();
	configUART();


    // Kiểm tra trạng thái của đèn LED
	while(1){
		for(uint8_t i = 0; i< 20; i++){
			buff[i] = 0;
		}

		check_mode(buff[10]);

	}
}

