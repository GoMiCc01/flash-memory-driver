################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/Flash/Core/flash_high_api.c \
../Components/Flash/Core/flash_low_api.c 

OBJS += \
./Components/Flash/Core/flash_high_api.o \
./Components/Flash/Core/flash_low_api.o 

C_DEPS += \
./Components/Flash/Core/flash_high_api.d \
./Components/Flash/Core/flash_low_api.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Flash/Core/%.o Components/Flash/Core/%.su Components/Flash/Core/%.cyclo: ../Components/Flash/Core/%.c Components/Flash/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Components/Filesystem -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Components/Flash/Inc -I../Middlewares/Third_party/LittleFS -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Components-2f-Flash-2f-Core

clean-Components-2f-Flash-2f-Core:
	-$(RM) ./Components/Flash/Core/flash_high_api.cyclo ./Components/Flash/Core/flash_high_api.d ./Components/Flash/Core/flash_high_api.o ./Components/Flash/Core/flash_high_api.su ./Components/Flash/Core/flash_low_api.cyclo ./Components/Flash/Core/flash_low_api.d ./Components/Flash/Core/flash_low_api.o ./Components/Flash/Core/flash_low_api.su

.PHONY: clean-Components-2f-Flash-2f-Core

