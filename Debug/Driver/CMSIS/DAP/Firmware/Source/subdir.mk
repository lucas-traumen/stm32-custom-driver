################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/DAP.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/DAP_vendor.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/JTAG_DP.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/SWO.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/SW_DP.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/UART.c 

OBJS += \
./Driver/CMSIS/DAP/Firmware/Source/DAP.o \
./Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.o \
./Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.o \
./Driver/CMSIS/DAP/Firmware/Source/SWO.o \
./Driver/CMSIS/DAP/Firmware/Source/SW_DP.o \
./Driver/CMSIS/DAP/Firmware/Source/UART.o 

C_DEPS += \
./Driver/CMSIS/DAP/Firmware/Source/DAP.d \
./Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.d \
./Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.d \
./Driver/CMSIS/DAP/Firmware/Source/SWO.d \
./Driver/CMSIS/DAP/Firmware/Source/SW_DP.d \
./Driver/CMSIS/DAP/Firmware/Source/UART.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/DAP/Firmware/Source/DAP.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/DAP.c Driver/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/DAP_vendor.c Driver/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/JTAG_DP.c Driver/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DAP/Firmware/Source/SWO.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/SWO.c Driver/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DAP/Firmware/Source/SW_DP.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/SW_DP.c Driver/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DAP/Firmware/Source/UART.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DAP/Firmware/Source/UART.c Driver/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-DAP-2f-Firmware-2f-Source

clean-Driver-2f-CMSIS-2f-DAP-2f-Firmware-2f-Source:
	-$(RM) ./Driver/CMSIS/DAP/Firmware/Source/DAP.cyclo ./Driver/CMSIS/DAP/Firmware/Source/DAP.d ./Driver/CMSIS/DAP/Firmware/Source/DAP.o ./Driver/CMSIS/DAP/Firmware/Source/DAP.su ./Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.cyclo ./Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.d ./Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.o ./Driver/CMSIS/DAP/Firmware/Source/DAP_vendor.su ./Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.cyclo ./Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.d ./Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.o ./Driver/CMSIS/DAP/Firmware/Source/JTAG_DP.su ./Driver/CMSIS/DAP/Firmware/Source/SWO.cyclo ./Driver/CMSIS/DAP/Firmware/Source/SWO.d ./Driver/CMSIS/DAP/Firmware/Source/SWO.o ./Driver/CMSIS/DAP/Firmware/Source/SWO.su ./Driver/CMSIS/DAP/Firmware/Source/SW_DP.cyclo ./Driver/CMSIS/DAP/Firmware/Source/SW_DP.d ./Driver/CMSIS/DAP/Firmware/Source/SW_DP.o ./Driver/CMSIS/DAP/Firmware/Source/SW_DP.su ./Driver/CMSIS/DAP/Firmware/Source/UART.cyclo ./Driver/CMSIS/DAP/Firmware/Source/UART.d ./Driver/CMSIS/DAP/Firmware/Source/UART.o ./Driver/CMSIS/DAP/Firmware/Source/UART.su

.PHONY: clean-Driver-2f-CMSIS-2f-DAP-2f-Firmware-2f-Source

