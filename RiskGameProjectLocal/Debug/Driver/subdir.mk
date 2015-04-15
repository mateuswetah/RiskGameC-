################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Driver/Game.cpp \
../Driver/GameDriver.cpp 

OBJS += \
./Driver/Game.o \
./Driver/GameDriver.o 

CPP_DEPS += \
./Driver/Game.d \
./Driver/GameDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/%.o: ../Driver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


