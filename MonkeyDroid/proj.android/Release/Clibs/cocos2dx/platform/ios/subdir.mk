################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/platform/ios/CCLock.cpp 

OBJS += \
./Clibs/cocos2dx/platform/ios/CCLock.o 

CPP_DEPS += \
./Clibs/cocos2dx/platform/ios/CCLock.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/platform/ios/CCLock.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/platform/ios/CCLock.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


