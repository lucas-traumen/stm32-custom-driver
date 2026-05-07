################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.c \
../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.c 

OBJS += \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o 

C_DEPS += \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d \
./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/QuaternionMathFunctions/%.o Driver/CSMIS/DSP/Source/QuaternionMathFunctions/%.su Driver/CSMIS/DSP/Source/QuaternionMathFunctions/%.cyclo: ../Driver/CSMIS/DSP/Source/QuaternionMathFunctions/%.c Driver/CSMIS/DSP/Source/QuaternionMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-QuaternionMathFunctions

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-QuaternionMathFunctions:
	-$(RM) ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.su ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.cyclo ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o ./Driver/CSMIS/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-QuaternionMathFunctions

