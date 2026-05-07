################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.c \
../Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.c 

OBJS += \
./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.o \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.o 

C_DEPS += \
./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.d \
./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CSMIS/DSP/Source/DistanceFunctions/%.o Driver/CSMIS/DSP/Source/DistanceFunctions/%.su Driver/CSMIS/DSP/Source/DistanceFunctions/%.cyclo: ../Driver/CSMIS/DSP/Source/DistanceFunctions/%.c Driver/CSMIS/DSP/Source/DistanceFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/Github/STM32F4/Peripheral/inc" -I"D:/Github/STM32F4/DSP" -I"D:/Github/STM32F4/DSP/Day1" -I"D:/Github/STM32F4/Driver/Core/Inc" -I"D:/Github/STM32F4/Peripheral" -I"D:/Github/STM32F4/Driver/CSMIS" -I"D:/Github/STM32F4/Driver/CSMIS/Device/ST/STM32F4xx/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Core/Include" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/Include" -I"D:/Github/STM32F4/Driver/CSMIS/Include" -I"D:/Github/STM32F4/Peripheral/src" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/PrivateInclude" -I"D:/Github/STM32F4/Driver/CSMIS/DSP/ComputeLibrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-DistanceFunctions

clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-DistanceFunctions:
	-$(RM) ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctions.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_boolean_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_braycurtis_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_canberra_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_chebyshev_distance_f64.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cityblock_distance_f64.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_correlation_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_cosine_distance_f64.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_dice_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.d
	-$(RM) ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_euclidean_distance_f64.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_hamming_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jaccard_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_jensenshannon_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_kulsinski_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f16.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_minkowski_distance_f32.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_rogerstanimoto_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_russellrao_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalmichener_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_sokalsneath_distance.su ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.cyclo ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.d ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.o ./Driver/CSMIS/DSP/Source/DistanceFunctions/arm_yule_distance.su

.PHONY: clean-Driver-2f-CSMIS-2f-DSP-2f-Source-2f-DistanceFunctions

