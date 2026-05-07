################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/fonts.c \
../Peripheral/src/st7735.c 

OBJS += \
./Peripheral/src/fonts.o \
./Peripheral/src/st7735.o 

C_DEPS += \
./Peripheral/src/fonts.d \
./Peripheral/src/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/%.o Peripheral/src/%.su Peripheral/src/%.cyclo: ../Peripheral/src/%.c Peripheral/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Peripheral-2f-src

clean-Peripheral-2f-src:
	-$(RM) ./Peripheral/src/fonts.cyclo ./Peripheral/src/fonts.d ./Peripheral/src/fonts.o ./Peripheral/src/fonts.su ./Peripheral/src/st7735.cyclo ./Peripheral/src/st7735.d ./Peripheral/src/st7735.o ./Peripheral/src/st7735.su

.PHONY: clean-Peripheral-2f-src

