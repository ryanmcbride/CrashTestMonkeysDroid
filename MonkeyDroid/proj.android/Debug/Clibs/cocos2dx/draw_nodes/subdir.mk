################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/draw_nodes/CCDrawNode.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/draw_nodes/CCDrawingPrimitives.cpp 

OBJS += \
./Clibs/cocos2dx/draw_nodes/CCDrawNode.o \
./Clibs/cocos2dx/draw_nodes/CCDrawingPrimitives.o 

CPP_DEPS += \
./Clibs/cocos2dx/draw_nodes/CCDrawNode.d \
./Clibs/cocos2dx/draw_nodes/CCDrawingPrimitives.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/draw_nodes/CCDrawNode.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/draw_nodes/CCDrawNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/draw_nodes/CCDrawingPrimitives.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/draw_nodes/CCDrawingPrimitives.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


