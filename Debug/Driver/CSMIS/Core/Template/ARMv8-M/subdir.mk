################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/Core/Template/ARMv8-M/main_s.c \
../Driver/CSMIS/Core/Template/ARMv8-M/tz_context.c 

OBJS += \
./Driver/CSMIS/Core/Template/ARMv8-M/main_s.o \
./Driver/CSMIS/Core/Template/ARMv8-M/tz_context.o 

C_DEPS += \
./Driver/CSMIS/Core/Template/ARMv8-M/main_s.d \
./Driver/CSMIS/Core/Template/ARMv8-M/tz_context.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/Core/Template/ARMv8-M/%.o Driver/CSMIS/Core/Template/ARMv8-M/%.su Driver/CSMIS/Core/Template/ARMv8-M/%.cyclo: ../Driver/CSMIS/Core/Template/ARMv8-M/%.c Driver/CSMIS/Core/Template/ARMv8-M/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-Core-2f-Template-2f-ARMv8-2d-M

clean-Driver-2f-CSMIS-2f-Core-2f-Template-2f-ARMv8-2d-M:
	-$(RM) ./Driver/CSMIS/Core/Template/ARMv8-M/main_s.cyclo ./Driver/CSMIS/Core/Template/ARMv8-M/main_s.d ./Driver/CSMIS/Core/Template/ARMv8-M/main_s.o ./Driver/CSMIS/Core/Template/ARMv8-M/main_s.su ./Driver/CSMIS/Core/Template/ARMv8-M/tz_context.cyclo ./Driver/CSMIS/Core/Template/ARMv8-M/tz_context.d ./Driver/CSMIS/Core/Template/ARMv8-M/tz_context.o ./Driver/CSMIS/Core/Template/ARMv8-M/tz_context.su

.PHONY: clean-Driver-2f-CSMIS-2f-Core-2f-Template-2f-ARMv8-2d-M

