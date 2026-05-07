################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Core/Src/exti.c \
../Driver/Core/Src/gpio.c \
../Driver/Core/Src/i2c_driver.c \
../Driver/Core/Src/init.c \
../Driver/Core/Src/it.c \
../Driver/Core/Src/rcc.c \
../Driver/Core/Src/spi_driver.c 

OBJS += \
./Driver/Core/Src/exti.o \
./Driver/Core/Src/gpio.o \
./Driver/Core/Src/i2c_driver.o \
./Driver/Core/Src/init.o \
./Driver/Core/Src/it.o \
./Driver/Core/Src/rcc.o \
./Driver/Core/Src/spi_driver.o 

C_DEPS += \
./Driver/Core/Src/exti.d \
./Driver/Core/Src/gpio.d \
./Driver/Core/Src/i2c_driver.d \
./Driver/Core/Src/init.d \
./Driver/Core/Src/it.d \
./Driver/Core/Src/rcc.d \
./Driver/Core/Src/spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Core/Src/%.o Driver/Core/Src/%.su Driver/Core/Src/%.cyclo: ../Driver/Core/Src/%.c Driver/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -I"D:/Github/STM32F4/Driver/Core/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Core-2f-Src

clean-Driver-2f-Core-2f-Src:
	-$(RM) ./Driver/Core/Src/exti.cyclo ./Driver/Core/Src/exti.d ./Driver/Core/Src/exti.o ./Driver/Core/Src/exti.su ./Driver/Core/Src/gpio.cyclo ./Driver/Core/Src/gpio.d ./Driver/Core/Src/gpio.o ./Driver/Core/Src/gpio.su ./Driver/Core/Src/i2c_driver.cyclo ./Driver/Core/Src/i2c_driver.d ./Driver/Core/Src/i2c_driver.o ./Driver/Core/Src/i2c_driver.su ./Driver/Core/Src/init.cyclo ./Driver/Core/Src/init.d ./Driver/Core/Src/init.o ./Driver/Core/Src/init.su ./Driver/Core/Src/it.cyclo ./Driver/Core/Src/it.d ./Driver/Core/Src/it.o ./Driver/Core/Src/it.su ./Driver/Core/Src/rcc.cyclo ./Driver/Core/Src/rcc.d ./Driver/Core/Src/rcc.o ./Driver/Core/Src/rcc.su ./Driver/Core/Src/spi_driver.cyclo ./Driver/Core/Src/spi_driver.d ./Driver/Core/Src/spi_driver.o ./Driver/Core/Src/spi_driver.su

.PHONY: clean-Driver-2f-Core-2f-Src

