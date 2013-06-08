################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/CocosDenshion/android/jni/SimpleAudioEngineJni.cpp 

OBJS += \
./Clibs/CocosDenshion/android/jni/SimpleAudioEngineJni.o 

CPP_DEPS += \
./Clibs/CocosDenshion/android/jni/SimpleAudioEngineJni.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/CocosDenshion/android/jni/SimpleAudioEngineJni.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/CocosDenshion/android/jni/SimpleAudioEngineJni.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


