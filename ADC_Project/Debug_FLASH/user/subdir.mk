################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/adc.c \
../user/clocks.c \
../user/gpio.c 

OBJS += \
./user/adc.o \
./user/clocks.o \
./user/gpio.o 

C_DEPS += \
./user/adc.d \
./user/clocks.d \
./user/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
user/%.o: ../user/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@user/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


