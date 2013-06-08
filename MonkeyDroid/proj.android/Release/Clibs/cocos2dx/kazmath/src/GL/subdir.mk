################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/kazmath/src/GL/mat4stack.c \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/kazmath/src/GL/matrix.c 

OBJS += \
./Clibs/cocos2dx/kazmath/src/GL/mat4stack.o \
./Clibs/cocos2dx/kazmath/src/GL/matrix.o 

C_DEPS += \
./Clibs/cocos2dx/kazmath/src/GL/mat4stack.d \
./Clibs/cocos2dx/kazmath/src/GL/matrix.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/kazmath/src/GL/mat4stack.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/kazmath/src/GL/mat4stack.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/kazmath/src/GL/matrix.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/kazmath/src/GL/matrix.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


