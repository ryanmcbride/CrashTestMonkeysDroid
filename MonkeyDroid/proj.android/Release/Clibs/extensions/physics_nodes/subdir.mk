################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/physics_nodes/CCPhysicsDebugNode.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/physics_nodes/CCPhysicsSprite.cpp 

OBJS += \
./Clibs/extensions/physics_nodes/CCPhysicsDebugNode.o \
./Clibs/extensions/physics_nodes/CCPhysicsSprite.o 

CPP_DEPS += \
./Clibs/extensions/physics_nodes/CCPhysicsDebugNode.d \
./Clibs/extensions/physics_nodes/CCPhysicsSprite.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/extensions/physics_nodes/CCPhysicsDebugNode.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/physics_nodes/CCPhysicsDebugNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/extensions/physics_nodes/CCPhysicsSprite.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/physics_nodes/CCPhysicsSprite.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


