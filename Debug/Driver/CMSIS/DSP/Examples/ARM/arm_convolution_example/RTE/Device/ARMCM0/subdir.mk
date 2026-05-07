################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.c 

OBJS += \
./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.o \
./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.o 

C_DEPS += \
./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.d \
./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.c Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.c Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_convolution_example-2f-RTE-2f-Device-2f-ARMCM0

clean-Driver-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_convolution_example-2f-RTE-2f-Device-2f-ARMCM0:
	-$(RM) ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.cyclo ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.d ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.o ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/startup_ARMCM0.su ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.cyclo ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.d ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.o ./Driver/CMSIS/DSP/Examples/ARM/arm_convolution_example/RTE/Device/ARMCM0/system_ARMCM0.su

.PHONY: clean-Driver-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_convolution_example-2f-RTE-2f-Device-2f-ARMCM0

