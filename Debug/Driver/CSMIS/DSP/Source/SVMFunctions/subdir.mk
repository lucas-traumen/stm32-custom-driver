################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.c \
../Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.c 

OBJS += \
./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.o \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.o 

C_DEPS += \
./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.d \
./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/SVMFunctions/%.o Driver/CSMIS/DSP/Source/SVMFunctions/%.su Driver/CSMIS/DSP/Source/SVMFunctions/%.cyclo: ../Driver/CSMIS/DSP/Source/SVMFunctions/%.c Driver/CSMIS/DSP/Source/SVMFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-SVMFunctions

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-SVMFunctions:
	-$(RM) ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.d ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.o ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctions.su ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/SVMFunctionsF16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.su ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.cyclo ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.d ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.o ./Driver/CSMIS/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-SVMFunctions

