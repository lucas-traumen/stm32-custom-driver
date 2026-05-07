################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.c 

OBJS += \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.o \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.o 

C_DEPS += \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.d \
./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.c Driver/CMSIS/NN/Source/SoftmaxFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-SoftmaxFunctions

clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-SoftmaxFunctions:
	-$(RM) ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_nn_softmax_common_s8.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q15.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_q7.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s16.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_s8_s16.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_u8.su ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.cyclo ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.d ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.o ./Driver/CMSIS/NN/Source/SoftmaxFunctions/arm_softmax_with_batch_q7.su

.PHONY: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-SoftmaxFunctions

