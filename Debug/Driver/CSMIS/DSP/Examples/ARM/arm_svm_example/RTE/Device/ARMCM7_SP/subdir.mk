################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.c \
../Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.c 

OBJS += \
./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.o \
./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.o 

C_DEPS += \
./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.d \
./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/%.o Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/%.su Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/%.cyclo: ../Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/%.c Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_svm_example-2f-RTE-2f-Device-2f-ARMCM7_SP

clean-Driver-2f-CSMIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_svm_example-2f-RTE-2f-Device-2f-ARMCM7_SP:
	-$(RM) ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.cyclo ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.d ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.o ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.su ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.cyclo ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.d ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.o ./Driver/CSMIS/DSP/Examples/ARM/arm_svm_example/RTE/Device/ARMCM7_SP/system_ARMCM7.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_svm_example-2f-RTE-2f-Device-2f-ARMCM7_SP

