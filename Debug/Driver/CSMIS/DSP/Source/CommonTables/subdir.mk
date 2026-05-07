################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/CommonTables/CommonTables.c \
../Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.c \
../Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.c \
../Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.c \
../Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.c \
../Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.c \
../Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.c \
../Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.c 

OBJS += \
./Driver/CSMIS/DSP/Source/CommonTables/CommonTables.o \
./Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.o \
./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.o \
./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.o \
./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.o \
./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.o \
./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.o \
./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.o 

C_DEPS += \
./Driver/CSMIS/DSP/Source/CommonTables/CommonTables.d \
./Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.d \
./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.d \
./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.d \
./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.d \
./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.d \
./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.d \
./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/CommonTables/%.o Driver/CSMIS/DSP/Source/CommonTables/%.su Driver/CSMIS/DSP/Source/CommonTables/%.cyclo: ../Driver/CSMIS/DSP/Source/CommonTables/%.c Driver/CSMIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-CommonTables

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./Driver/CSMIS/DSP/Source/CommonTables/CommonTables.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/CommonTables.d ./Driver/CSMIS/DSP/Source/CommonTables/CommonTables.o ./Driver/CSMIS/DSP/Source/CommonTables/CommonTables.su ./Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.d ./Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.o ./Driver/CSMIS/DSP/Source/CommonTables/CommonTablesF16.su ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.d ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.o ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables.su ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.d ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.o ./Driver/CSMIS/DSP/Source/CommonTables/arm_common_tables_f16.su ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.d ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.o ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs.su ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.d ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.o ./Driver/CSMIS/DSP/Source/CommonTables/arm_const_structs_f16.su ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.d ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.o ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables.su ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.cyclo ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.d ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.o ./Driver/CSMIS/DSP/Source/CommonTables/arm_mve_tables_f16.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-CommonTables

