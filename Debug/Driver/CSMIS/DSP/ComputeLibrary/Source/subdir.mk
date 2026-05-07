################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.c 

OBJS += \
./Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.o 

C_DEPS += \
./Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/ComputeLibrary/Source/%.o Driver/CSMIS/DSP/ComputeLibrary/Source/%.su Driver/CSMIS/DSP/ComputeLibrary/Source/%.cyclo: ../Driver/CSMIS/DSP/ComputeLibrary/Source/%.c Driver/CSMIS/DSP/ComputeLibrary/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-ComputeLibrary-2f-Source

clean-Driver-2f-CSMIS-2f-DSP-2f-ComputeLibrary-2f-Source:
	-$(RM) ./Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.cyclo ./Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.d ./Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.o ./Driver/CSMIS/DSP/ComputeLibrary/Source/arm_cl_tables.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-ComputeLibrary-2f-Source

