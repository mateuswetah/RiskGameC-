################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Map/Continent.cpp \
../Map/Map.cpp \
../Map/Territory.cpp 

OBJS += \
./Map/Continent.o \
./Map/Map.o \
./Map/Territory.o 

CPP_DEPS += \
./Map/Continent.d \
./Map/Map.d \
./Map/Territory.d 


# Each subdirectory must supply rules for building sources it contributes
Map/%.o: ../Map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


