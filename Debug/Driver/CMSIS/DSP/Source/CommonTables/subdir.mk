################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.c \
D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.c 

OBJS += \
./Driver/CMSIS/DSP/Source/CommonTables/CommonTables.o \
./Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o \
./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.o \
./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.o \
./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.o \
./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.o \
./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.o \
./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.o 

C_DEPS += \
./Driver/CMSIS/DSP/Source/CommonTables/CommonTables.d \
./Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.d \
./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.d \
./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.d \
./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.d \
./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.d \
./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.d \
./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CMSIS/DSP/Source/CommonTables/CommonTables.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.o: D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.c Driver/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Core/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Github/stm32/stm32_linux_F4/Core/Inc" -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/Include" -I"D:/Github/stm32/stm32_linux_F4/Drivers/CMSIS/DSP/PrivateInclude" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

clean-Driver-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./Driver/CMSIS/DSP/Source/CommonTables/CommonTables.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/CommonTables.d ./Driver/CMSIS/DSP/Source/CommonTables/CommonTables.o ./Driver/CMSIS/DSP/Source/CommonTables/CommonTables.su ./Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.d ./Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o ./Driver/CMSIS/DSP/Source/CommonTables/CommonTablesF16.su ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.d ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.o ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables.su ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.d ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.o ./Driver/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.su ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.d ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.o ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs.su ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.d ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.o ./Driver/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.su ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.d ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.o ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables.su ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.cyclo ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.d ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.o ./Driver/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.su

.PHONY: clean-Driver-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

