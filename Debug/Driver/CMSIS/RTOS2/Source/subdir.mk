################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/RTOS2/Source/os_systick.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/RTOS2/Source/os_tick_gtim.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/RTOS2/Source/os_tick_ptim.c 

OBJS += \
./Driver/CMSIS/RTOS2/Source/os_systick.o \
./Driver/CMSIS/RTOS2/Source/os_tick_gtim.o \
./Driver/CMSIS/RTOS2/Source/os_tick_ptim.o 

C_DEPS += \
./Driver/CMSIS/RTOS2/Source/os_systick.d \
./Driver/CMSIS/RTOS2/Source/os_tick_gtim.d \
./Driver/CMSIS/RTOS2/Source/os_tick_ptim.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/RTOS2/Source/os_systick.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/RTOS2/Source/os_systick.c Driver/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/RTOS2/Source/os_tick_gtim.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/RTOS2/Source/os_tick_gtim.c Driver/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/RTOS2/Source/os_tick_ptim.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/RTOS2/Source/os_tick_ptim.c Driver/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-RTOS2-2f-Source

clean-Driver-2f-CMSIS-2f-RTOS2-2f-Source:
	-$(RM) ./Driver/CMSIS/RTOS2/Source/os_systick.cyclo ./Driver/CMSIS/RTOS2/Source/os_systick.d ./Driver/CMSIS/RTOS2/Source/os_systick.o ./Driver/CMSIS/RTOS2/Source/os_systick.su ./Driver/CMSIS/RTOS2/Source/os_tick_gtim.cyclo ./Driver/CMSIS/RTOS2/Source/os_tick_gtim.d ./Driver/CMSIS/RTOS2/Source/os_tick_gtim.o ./Driver/CMSIS/RTOS2/Source/os_tick_gtim.su ./Driver/CMSIS/RTOS2/Source/os_tick_ptim.cyclo ./Driver/CMSIS/RTOS2/Source/os_tick_ptim.d ./Driver/CMSIS/RTOS2/Source/os_tick_ptim.o ./Driver/CMSIS/RTOS2/Source/os_tick_ptim.su

.PHONY: clean-Driver-2f-CMSIS-2f-RTOS2-2f-Source

