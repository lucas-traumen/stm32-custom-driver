################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.c 

OBJS += \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.o \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.o 

C_DEPS += \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.d \
./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.c Driver/CMSIS/NN/Source/FullyConnectedFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-FullyConnectedFunctions

clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-FullyConnectedFunctions:
	-$(RM) ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s16.su ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.cyclo ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.d ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.o ./Driver/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_s8.su

.PHONY: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-FullyConnectedFunctions

