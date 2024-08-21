################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/Timers/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EX_INT/subdir.mk
-include MCAL/DIO/subdir.mk
-include LIB/DELAY/subdir.mk
-include HAL/keypad/subdir.mk
-include HAL/Servo/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/IR_sensor/subdir.mk
-include HAL/Button/subdir.mk
-include Communication/Maset_Slave_COMM/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Gate_system.lss \

FLASH_IMAGE += \
Gate_system.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Gate_system.elf secondary-outputs

# Tool invocations
Gate_system.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Gate_system.map -mmcu=atmega32 -o "Gate_system.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Gate_system.lss: Gate_system.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Gate_system.elf  >"Gate_system.lss"
	@echo 'Finished building: $@'
	@echo ' '

Gate_system.hex: Gate_system.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Gate_system.elf  "Gate_system.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Gate_system.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Gate_system.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Gate_system.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
