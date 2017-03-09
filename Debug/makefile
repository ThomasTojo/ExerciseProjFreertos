################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include freertos/src/subdir.mk
-include example/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ExerciseProjFreertos.axf

# Tool invocations
ExerciseProjFreertos.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Thomas\Documents\LPCXpresso_8.2.2_650\workspace\lpc_chip_18xx\Debug" -L"C:\Users\Thomas\Documents\LPCXpresso_8.2.2_650\workspace\lpc_board_keil_mcb_1857\Debug" -Xlinker -Map="ExerciseProjFreertos.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "ExerciseProjFreertos_Debug.ld" -o "ExerciseProjFreertos.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) ExerciseProjFreertos.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ExerciseProjFreertos.axf"; # arm-none-eabi-objcopy -v -O binary "ExerciseProjFreertos.axf" "ExerciseProjFreertos.bin" ; # checksum -p LPC1857 -d "ExerciseProjFreertos.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
