################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Player/AIPlayer.cpp \
../Player/Card.cpp \
../Player/Player.cpp 

OBJS += \
./Player/AIPlayer.o \
./Player/Card.o \
./Player/Player.o 

CPP_DEPS += \
./Player/AIPlayer.d \
./Player/Card.d \
./Player/Player.d 


# Each subdirectory must supply rules for building sources it contributes
Player/%.o: ../Player/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

