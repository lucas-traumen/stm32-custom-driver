################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Template/ARMv8-M/main_s.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Template/ARMv8-M/tz_context.c 

OBJS += \
./Driver/CMSIS/Core/Template/ARMv8-M/main_s.o \
./Driver/CMSIS/Core/Template/ARMv8-M/tz_context.o 

C_DEPS += \
./Driver/CMSIS/Core/Template/ARMv8-M/main_s.d \
./Driver/CMSIS/Core/Template/ARMv8-M/tz_context.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/Core/Template/ARMv8-M/main_s.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Template/ARMv8-M/main_s.c Driver/CMSIS/Core/Template/ARMv8-M/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/Core/Template/ARMv8-M/tz_context.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Template/ARMv8-M/tz_context.c Driver/CMSIS/Core/Template/ARMv8-M/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-Core-2f-Template-2f-ARMv8-2d-M

clean-Driver-2f-CMSIS-2f-Core-2f-Template-2f-ARMv8-2d-M:
	-$(RM) ./Driver/CMSIS/Core/Template/ARMv8-M/main_s.cyclo ./Driver/CMSIS/Core/Template/ARMv8-M/main_s.d ./Driver/CMSIS/Core/Template/ARMv8-M/main_s.o ./Driver/CMSIS/Core/Template/ARMv8-M/main_s.su ./Driver/CMSIS/Core/Template/ARMv8-M/tz_context.cyclo ./Driver/CMSIS/Core/Template/ARMv8-M/tz_context.d ./Driver/CMSIS/Core/Template/ARMv8-M/tz_context.o ./Driver/CMSIS/Core/Template/ARMv8-M/tz_context.su

.PHONY: clean-Driver-2f-CMSIS-2f-Core-2f-Template-2f-ARMv8-2d-M

