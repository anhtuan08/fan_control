
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
*Khi gửi một chuỗi sai về ID hoặc lỗi không xác định sẽ luôn luôn gửi về là 0x02 0xff 0x01 0xff 0x00
*Khi chuyển từ điều khiển UART sang SWITCH thì trạng thái của LED sẽ luôn là 0
*Mode Fan Speed:
    - Set mode 0: 0%
    - Set mode 1: 30%
    - Set mode 2: 60%
    - Set mode 3: 90%

Co nhieu truong hop xay ra trong control fan:
Viec thuc hien chuyen mode:

frame uart:

Start: luoon luon la 02 (the hien cho viec nhan)

ID: Day co the la che do bat/ tat Led (hien tai se chua config)

Length: Config co dinh (01)

Mode: 01 - UART 02 - SW

Stop: Bit dung: bit nay se the hien che do mode fan speed

	*Mode Fan Speed:
    - Set mode 0: 0%
    - Set mode 1: 30%
    - Set mode 2: 60%
    - Set mode 3: 90%

Khi chuyen mode thi trang thi se bi reset: LED = 0

Viec check:

Phai check dung day UART command string, neu khong dung thi tra ve 0x02 0xff 0x01 0xff 0x00 (tra ve tren terminal)

Viec chuyen che do se duoc check o bit Mode: 01, 02

Chi su dung duoc 1 mode, su dung mode SW thi khong the command UART. Neu muon su dung dung sang UART thi se phai command dung


 * */





#include "led.h"
#include "button.h"
#include "PWM.h"
#include "UART.h"
#include "delay.h"

int count = 0;
int msTick = 0;

uint8_t data = 0;

uint32_t buff[LENGTH];

uint8_t count_bit_0 = 0;

uint8_t count_3_bit = 0;

uint8_t count_mode_bit = 0;

uint8_t check_length_string = 0;


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
	}
}

void Button_mode(){
//	while(count_mode_bit != 1){
		turn_on_red_led();
		if(count > 3){
			count = 0;
		}
		check_count(count);
//	}
}


void reset_buff(){
	for(uint8_t i = 0; i < LENGTH; i++){
			buff[i] = 0;
	}
}

void switch_mode(){
	if(count_mode_bit == 1){
			check_id_bit(buff);
	}
	else if(count_mode_bit == 2){
			Button_mode();
	}
	else{
		return_default();
	}
}


void uart_mode(){
	check_length_string = check_length(data);
	if(check_length_string == 1){
		count_bit_0 = check_buff_0(buff, LENGTH);
			if(count_bit_0 == 5){
				count_3_bit = check_start_bit(buff);
					if(count_3_bit == 1){
						count_mode_bit = check_mode(buff);
							switch_mode();
					}
					else{
						return_default();
				}
		}
	}
	else{
		return_default();
		}
	}

int main(){

	sys_Timer();
	initButton();
	statusButton();
	configPWM();
	configUART();



    // Kiểm tra trạng thái của đèn LED
	while(1){

		uart_mode();

	}
}

