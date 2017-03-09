################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/ExerciseProjFreertos.c \
../example/src/cr_startup_lpc18xx.c \
../example/src/sysinit.c 

OBJS += \
./example/src/ExerciseProjFreertos.o \
./example/src/cr_startup_lpc18xx.o \
./example/src/sysinit.o 

C_DEPS += \
./example/src/ExerciseProjFreertos.d \
./example/src/cr_startup_lpc18xx.d \
./example/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\Thomas\Documents\LPCXpresso_8.2.2_650\workspace\lpc_chip_18xx\inc" -I"C:\Users\Thomas\Documents\LPCXpresso_8.2.2_650\workspace\lpc_board_keil_mcb_1857\inc" -I"C:\Users\Thomas\Documents\LPCXpresso_8.2.2_650\workspace\ExerciseProjFreertos\example\inc" -I"C:\Users\Thomas\Documents\LPCXpresso_8.2.2_650\workspace\ExerciseProjFreertos\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


