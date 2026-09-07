################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Flash/Core/high_api.c 

OBJS += \
./Drivers/Flash/Core/high_api.o 

C_DEPS += \
./Drivers/Flash/Core/high_api.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Flash/Core/%.o Drivers/Flash/Core/%.su Drivers/Flash/Core/%.cyclo: ../Drivers/Flash/Core/%.c Drivers/Flash/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/Flash/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Flash-2f-Core

clean-Drivers-2f-Flash-2f-Core:
	-$(RM) ./Drivers/Flash/Core/high_api.cyclo ./Drivers/Flash/Core/high_api.d ./Drivers/Flash/Core/high_api.o ./Drivers/Flash/Core/high_api.su

.PHONY: clean-Drivers-2f-Flash-2f-Core

