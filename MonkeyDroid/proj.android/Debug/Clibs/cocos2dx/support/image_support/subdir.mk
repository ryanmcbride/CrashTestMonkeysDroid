################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/image_support/TGAlib.cpp 

OBJS += \
./Clibs/cocos2dx/support/image_support/TGAlib.o 

CPP_DEPS += \
./Clibs/cocos2dx/support/image_support/TGAlib.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/support/image_support/TGAlib.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/image_support/TGAlib.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


