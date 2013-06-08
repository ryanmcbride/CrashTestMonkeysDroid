################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/Box2D/Rope/b2Rope.cpp 

OBJS += \
./Clibs/Box2D/Rope/b2Rope.o 

CPP_DEPS += \
./Clibs/Box2D/Rope/b2Rope.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/Box2D/Rope/b2Rope.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/Box2D/Rope/b2Rope.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


