# fan_control
This is a project embedded to control fan using MCU - MKL46z. 

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


