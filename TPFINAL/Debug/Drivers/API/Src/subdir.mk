################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/driver_sensor.c \
../Drivers/API/Src/driver_uart.c 

OBJS += \
./Drivers/API/Src/driver_sensor.o \
./Drivers/API/Src/driver_uart.o 

C_DEPS += \
./Drivers/API/Src/driver_sensor.d \
./Drivers/API/Src/driver_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/thony/Documents/Maestria/ProgramacionMicrocontroladores/repositorio/ProgramacionMicrocontroladores/TPFINAL/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/driver_sensor.cyclo ./Drivers/API/Src/driver_sensor.d ./Drivers/API/Src/driver_sensor.o ./Drivers/API/Src/driver_sensor.su ./Drivers/API/Src/driver_uart.cyclo ./Drivers/API/Src/driver_uart.d ./Drivers/API/Src/driver_uart.o ./Drivers/API/Src/driver_uart.su

.PHONY: clean-Drivers-2f-API-2f-Src
