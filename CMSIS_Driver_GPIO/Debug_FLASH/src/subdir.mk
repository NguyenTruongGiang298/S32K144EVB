################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Driver_GPIO.c \
../src/Driver_PORT.c \
../src/GPIO_MCAL.c \
../src/PORT_MCAL.c \
../src/main.c 

OBJS += \
./src/Driver_GPIO.o \
./src/Driver_PORT.o \
./src/GPIO_MCAL.o \
./src/PORT_MCAL.o \
./src/main.o 

C_DEPS += \
./src/Driver_GPIO.d \
./src/Driver_PORT.d \
./src/GPIO_MCAL.d \
./src/PORT_MCAL.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Driver_GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


