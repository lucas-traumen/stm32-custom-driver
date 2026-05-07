################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.c 

OBJS += \
./Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.o 

C_DEPS += \
./Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.c Driver/CMSIS/DSP/ComputeLibrary/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-DSP-2f-ComputeLibrary-2f-Source

clean-Driver-2f-CMSIS-2f-DSP-2f-ComputeLibrary-2f-Source:
	-$(RM) ./Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.cyclo ./Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.d ./Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.o ./Driver/CMSIS/DSP/ComputeLibrary/Source/arm_cl_tables.su

.PHONY: clean-Driver-2f-CMSIS-2f-DSP-2f-ComputeLibrary-2f-Source

