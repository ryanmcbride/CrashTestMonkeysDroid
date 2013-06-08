################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/base_nodes/CCAtlasNode.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/base_nodes/CCNode.cpp 

OBJS += \
./Clibs/cocos2dx/base_nodes/CCAtlasNode.o \
./Clibs/cocos2dx/base_nodes/CCNode.o 

CPP_DEPS += \
./Clibs/cocos2dx/base_nodes/CCAtlasNode.d \
./Clibs/cocos2dx/base_nodes/CCNode.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/base_nodes/CCAtlasNode.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/base_nodes/CCAtlasNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/base_nodes/CCNode.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/base_nodes/CCNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


