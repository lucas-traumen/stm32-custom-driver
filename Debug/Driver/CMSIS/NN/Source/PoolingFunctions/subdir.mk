################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.c 

OBJS += \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.o \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.o \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.o \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.o \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.o 

C_DEPS += \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.d \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.d \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.d \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.d \
./Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.c Driver/CMSIS/NN/Source/PoolingFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.c Driver/CMSIS/NN/Source/PoolingFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.c Driver/CMSIS/NN/Source/PoolingFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.c Driver/CMSIS/NN/Source/PoolingFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.c Driver/CMSIS/NN/Source/PoolingFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-PoolingFunctions

clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-PoolingFunctions:
	-$(RM) ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.cyclo ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.d ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.o ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s16.su ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.cyclo ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.d ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.o ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_avgpool_s8.su ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.cyclo ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.d ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.o ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s16.su ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.cyclo ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.d ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.o ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_max_pool_s8.su ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.cyclo ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.d ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.o ./Driver/CMSIS/NN/Source/PoolingFunctions/arm_pool_q7_HWC.su

.PHONY: clean-Driver-2f-CMSIS-2f-NN-2f-Source-2f-PoolingFunctions

