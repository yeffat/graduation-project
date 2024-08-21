################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EX_INT/subdir.mk
-include MCAL/DIO/subdir.mk
-include LIB/DELAY/subdir.mk
-include HAL/Stepper_Motor/subdir.mk
-include HAL/SEV_SEG/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/IR_HW-201/subdir.mk
-include HAL/ESP8266/subdir.mk
-include HAL/EEPROM/subdir.mk
-include Communication/WIFI_Server/subdir.mk
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
Main_System.lss \

FLASH_IMAGE += \
Main_System.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Main_System.elf secondary-outputs

# Tool invocations
Main_System.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Main_System.map -mmcu=atmega32 -o "Main_System.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Main_System.lss: Main_System.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Main_System.elf  >"Main_System.lss"
	@echo 'Finished building: $@'
	@echo ' '

Main_System.hex: Main_System.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Main_System.elf  "Main_System.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Main_System.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Main_System.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Main_System.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
