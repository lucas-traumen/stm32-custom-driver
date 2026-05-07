################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.c \
../Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.c 

OBJS += \
./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.o \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.o 

C_DEPS += \
./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.d \
./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/SupportFunctions/%.o Driver/CSMIS/DSP/Source/SupportFunctions/%.su Driver/CSMIS/DSP/Source/SupportFunctions/%.cyclo: ../Driver/CSMIS/DSP/Source/SupportFunctions/%.c Driver/CSMIS/DSP/Source/SupportFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-SupportFunctions

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-SupportFunctions:
	-$(RM) ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.d ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.o ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctions.su ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/SupportFunctionsF16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_barycenter_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_f64.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q15.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q31.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_copy_q7.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_float.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_f16_to_q15.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_f64.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q15.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q31.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_fill_q7.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_f16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q15.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q31.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_float_to_q7.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.cyclo
	-$(RM) ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_f16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_float.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q31.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q15_to_q7.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_float.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q15.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q31_to_q7.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_float.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q15.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_q7_to_q31.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_sort_init_f32.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.su ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.cyclo ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.d ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.o ./Driver/CSMIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-SupportFunctions

