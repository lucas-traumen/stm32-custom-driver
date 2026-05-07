################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.c \
../Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.c 

OBJS += \
./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.o \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.o 

C_DEPS += \
./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.d \
./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/MatrixFunctions/%.o Driver/CSMIS/DSP/Source/MatrixFunctions/%.su Driver/CSMIS/DSP/Source/MatrixFunctions/%.cyclo: ../Driver/CSMIS/DSP/Source/MatrixFunctions/%.c Driver/CSMIS/DSP/Source/MatrixFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-MatrixFunctions

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-MatrixFunctions:
	-$(RM) ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctions.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.o
	-$(RM) ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.o
	-$(RM) ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.su ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.cyclo ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.d ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.o ./Driver/CSMIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-MatrixFunctions

