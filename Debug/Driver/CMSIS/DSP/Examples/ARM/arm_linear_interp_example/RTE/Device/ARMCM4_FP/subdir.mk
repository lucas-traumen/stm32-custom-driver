################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.c 

OBJS += \
./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.o \
./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.o 

C_DEPS += \
./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.d \
./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.c Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.c Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_linear_interp_example-2f-RTE-2f-Device-2f-ARMCM4_FP

clean-Driver-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_linear_interp_example-2f-RTE-2f-Device-2f-ARMCM4_FP:
	-$(RM) ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.cyclo ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.d ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.o ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/startup_ARMCM4.su ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.cyclo ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.d ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.o ./Driver/CMSIS/DSP/Examples/ARM/arm_linear_interp_example/RTE/Device/ARMCM4_FP/system_ARMCM4.su

.PHONY: clean-Driver-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_linear_interp_example-2f-RTE-2f-Device-2f-ARMCM4_FP

