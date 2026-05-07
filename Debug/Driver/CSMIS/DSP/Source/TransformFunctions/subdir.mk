################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.c \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.c 

S_UPPER_SRCS += \
../Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.S 

OBJS += \
./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.o \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.o 

S_UPPER_DEPS += \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.d 

C_DEPS += \
./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.d \
./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/TransformFunctions/%.o Driver/CSMIS/DSP/Source/TransformFunctions/%.su Driver/CSMIS/DSP/Source/TransformFunctions/%.cyclo: ../Driver/CSMIS/DSP/Source/TransformFunctions/%.c Driver/CSMIS/DSP/Source/TransformFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Driver/CSMIS/DSP/Source/TransformFunctions/%.o: ../Driver/CSMIS/DSP/Source/TransformFunctions/%.S Driver/CSMIS/DSP/Source/TransformFunctions/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-TransformFunctions

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-TransformFunctions:
	-$(RM) ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.d ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.o ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctions.su ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/TransformFunctionsF16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal2.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_bitreversal_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_f64.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_f64.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_init_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.cyclo
	-$(RM) ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_dct4_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.d
	-$(RM) ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_init_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_mfcc_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_f64.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f16.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f64.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q15.su ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.cyclo ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.d ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.o ./Driver/CSMIS/DSP/Source/TransformFunctions/arm_rfft_q31.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-TransformFunctions

