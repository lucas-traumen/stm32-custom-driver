################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Core/Src/exti.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/gpio.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/init.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/it.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/rcc.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/spi_driver.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/system_stm32f4xx.c \
D:/Github/stm32/stm32_linux_F4/Core/Src/timer_driver.c 

OBJS += \
./Driver/Src/exti.o \
./Driver/Src/gpio.o \
./Driver/Src/init.o \
./Driver/Src/it.o \
./Driver/Src/rcc.o \
./Driver/Src/spi_driver.o \
./Driver/Src/system_stm32f4xx.o \
./Driver/Src/timer_driver.o 

C_DEPS += \
./Driver/Src/exti.d \
./Driver/Src/gpio.d \
./Driver/Src/init.d \
./Driver/Src/it.d \
./Driver/Src/rcc.d \
./Driver/Src/spi_driver.d \
./Driver/Src/system_stm32f4xx.d \
./Driver/Src/timer_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/exti.o: D:/Github/stm32/stm32_linux_F4/Core/Src/exti.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/gpio.o: D:/Github/stm32/stm32_linux_F4/Core/Src/gpio.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/init.o: D:/Github/stm32/stm32_linux_F4/Core/Src/init.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/it.o: D:/Github/stm32/stm32_linux_F4/Core/Src/it.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/rcc.o: D:/Github/stm32/stm32_linux_F4/Core/Src/rcc.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/spi_driver.o: D:/Github/stm32/stm32_linux_F4/Core/Src/spi_driver.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/system_stm32f4xx.o: D:/Github/stm32/stm32_linux_F4/Core/Src/system_stm32f4xx.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/Src/timer_driver.o: D:/Github/stm32/stm32_linux_F4/Core/Src/timer_driver.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/exti.cyclo ./Driver/Src/exti.d ./Driver/Src/exti.o ./Driver/Src/exti.su ./Driver/Src/gpio.cyclo ./Driver/Src/gpio.d ./Driver/Src/gpio.o ./Driver/Src/gpio.su ./Driver/Src/init.cyclo ./Driver/Src/init.d ./Driver/Src/init.o ./Driver/Src/init.su ./Driver/Src/it.cyclo ./Driver/Src/it.d ./Driver/Src/it.o ./Driver/Src/it.su ./Driver/Src/rcc.cyclo ./Driver/Src/rcc.d ./Driver/Src/rcc.o ./Driver/Src/rcc.su ./Driver/Src/spi_driver.cyclo ./Driver/Src/spi_driver.d ./Driver/Src/spi_driver.o ./Driver/Src/spi_driver.su ./Driver/Src/system_stm32f4xx.cyclo ./Driver/Src/system_stm32f4xx.d ./Driver/Src/system_stm32f4xx.o ./Driver/Src/system_stm32f4xx.su ./Driver/Src/timer_driver.cyclo ./Driver/Src/timer_driver.d ./Driver/Src/timer_driver.o ./Driver/Src/timer_driver.su

.PHONY: clean-Driver-2f-Src

