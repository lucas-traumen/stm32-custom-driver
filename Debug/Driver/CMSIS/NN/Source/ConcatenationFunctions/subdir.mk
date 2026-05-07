################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.c 

OBJS += \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.o \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.o \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.o \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.o 

C_DEPS += \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.d \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.d \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.d \
./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.c Driver/CMSIS/NN/Source/ConcatenationFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.c Driver/CMSIS/NN/Source/ConcatenationFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.c Driver/CMSIS/NN/Source/ConcatenationFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.c Driver/CMSIS/NN/Source/ConcatenationFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-ConcatenationFunctions

clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-ConcatenationFunctions:
	-$(RM) ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.cyclo ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.d ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.o ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_w.su ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.cyclo ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.d ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.o ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_x.su ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.cyclo ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.d ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.o ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_y.su ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.cyclo ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.d ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.o ./Driver/CMSIS/NN/Source/ConcatenationFunctions/arm_concatenation_s8_z.su

.PHONY: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-ConcatenationFunctions

