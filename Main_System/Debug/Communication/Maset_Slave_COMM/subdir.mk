################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Communication/Maset_Slave_COMM/Master_prog.c 

OBJS += \
./Communication/Maset_Slave_COMM/Master_prog.o 

C_DEPS += \
./Communication/Maset_Slave_COMM/Master_prog.d 


# Each subdirectory must supply rules for building sources it contributes
Communication/Maset_Slave_COMM/%.o: ../Communication/Maset_Slave_COMM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


