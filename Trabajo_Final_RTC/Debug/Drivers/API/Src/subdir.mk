################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_adc.c \
../Drivers/API/Src/API_debounce.c \
../Drivers/API/Src/API_delay.c \
../Drivers/API/Src/API_rcc.c \
../Drivers/API/Src/API_rtc.c \
../Drivers/API/Src/API_temperature.c \
../Drivers/API/Src/API_uart.c 

OBJS += \
./Drivers/API/Src/API_adc.o \
./Drivers/API/Src/API_debounce.o \
./Drivers/API/Src/API_delay.o \
./Drivers/API/Src/API_rcc.o \
./Drivers/API/Src/API_rtc.o \
./Drivers/API/Src/API_temperature.o \
./Drivers/API/Src/API_uart.o 

C_DEPS += \
./Drivers/API/Src/API_adc.d \
./Drivers/API/Src/API_debounce.d \
./Drivers/API/Src/API_delay.d \
./Drivers/API/Src/API_rcc.d \
./Drivers/API/Src/API_rtc.d \
./Drivers/API/Src/API_temperature.d \
./Drivers/API/Src/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"D:/UBA/5_Programacion_microcontroladores/PdM_workspace/Trabajo_Final_RTC/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/UBA/5_Programacion_microcontroladores/PdM_workspace/Trabajo_Final_RTC/Drivers/CMSIS/Include" -I"D:/UBA/5_Programacion_microcontroladores/PdM_workspace/Trabajo_Final_RTC/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/UBA/5_Programacion_microcontroladores/PdM_workspace/Trabajo_Final_RTC/Drivers/BSP/STM32F4xx_Nucleo_144" -I"D:/UBA/5_Programacion_microcontroladores/PdM_workspace/Trabajo_Final_RTC/Drivers/Core/Inc" -I"D:/UBA/5_Programacion_microcontroladores/PdM_workspace/Trabajo_Final_RTC/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_adc.cyclo ./Drivers/API/Src/API_adc.d ./Drivers/API/Src/API_adc.o ./Drivers/API/Src/API_adc.su ./Drivers/API/Src/API_debounce.cyclo ./Drivers/API/Src/API_debounce.d ./Drivers/API/Src/API_debounce.o ./Drivers/API/Src/API_debounce.su ./Drivers/API/Src/API_delay.cyclo ./Drivers/API/Src/API_delay.d ./Drivers/API/Src/API_delay.o ./Drivers/API/Src/API_delay.su ./Drivers/API/Src/API_rcc.cyclo ./Drivers/API/Src/API_rcc.d ./Drivers/API/Src/API_rcc.o ./Drivers/API/Src/API_rcc.su ./Drivers/API/Src/API_rtc.cyclo ./Drivers/API/Src/API_rtc.d ./Drivers/API/Src/API_rtc.o ./Drivers/API/Src/API_rtc.su ./Drivers/API/Src/API_temperature.cyclo ./Drivers/API/Src/API_temperature.d ./Drivers/API/Src/API_temperature.o ./Drivers/API/Src/API_temperature.su ./Drivers/API/Src/API_uart.cyclo ./Drivers/API/Src/API_uart.d ./Drivers/API/Src/API_uart.o ./Drivers/API/Src/API_uart.su

.PHONY: clean-Drivers-2f-API-2f-Src

