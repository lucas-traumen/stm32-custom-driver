################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP/Day1/signals.c 

OBJS += \
./DSP/Day1/signals.o 

C_DEPS += \
./DSP/Day1/signals.d 


# Each subdirectory must supply rules for building sources it contributes
DSP/Day1/%.o DSP/Day1/%.su DSP/Day1/%.cyclo: ../DSP/Day1/%.c DSP/Day1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -I"D:/Github/STM32F4/Driver/Core/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DSP-2f-Day1

clean-DSP-2f-Day1:
	-$(RM) ./DSP/Day1/signals.cyclo ./DSP/Day1/signals.d ./DSP/Day1/signals.o ./DSP/Day1/signals.su

.PHONY: clean-DSP-2f-Day1

