################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Fan_control.c \
../source/PWM.c \
../source/UART.c \
../source/button.c \
../source/delay.c \
../source/global.c \
../source/led.c 

C_DEPS += \
./source/Fan_control.d \
./source/PWM.d \
./source/UART.d \
./source/button.d \
./source/delay.d \
./source/global.d \
./source/led.d 

OBJS += \
./source/Fan_control.o \
./source/PWM.o \
./source/UART.o \
./source/button.o \
./source/delay.o \
./source/global.o \
./source/led.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"E:\Projects\MK46z_MCU\Fan_control\board" -I"E:\Projects\MK46z_MCU\Fan_control\source" -I"E:\Projects\MK46z_MCU\Fan_control" -I"E:\Projects\MK46z_MCU\Fan_control\drivers" -I"E:\Projects\MK46z_MCU\Fan_control\CMSIS" -I"E:\Projects\MK46z_MCU\Fan_control\startup" -I"E:\Projects\MK46z_MCU\Fan_control\utilities" -I"E:\Projects\MK46z_MCU\Fan_control\CMSIS_driver" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Fan_control.d ./source/Fan_control.o ./source/PWM.d ./source/PWM.o ./source/UART.d ./source/UART.o ./source/button.d ./source/button.o ./source/delay.d ./source/delay.o ./source/global.d ./source/global.o ./source/led.d ./source/led.o

.PHONY: clean-source

