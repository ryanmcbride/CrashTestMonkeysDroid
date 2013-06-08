################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/CocosDenshion/android/opensl/OpenSLEngine.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/CocosDenshion/android/opensl/SimpleAudioEngineOpenSL.cpp 

OBJS += \
./Clibs/CocosDenshion/android/opensl/OpenSLEngine.o \
./Clibs/CocosDenshion/android/opensl/SimpleAudioEngineOpenSL.o 

CPP_DEPS += \
./Clibs/CocosDenshion/android/opensl/OpenSLEngine.d \
./Clibs/CocosDenshion/android/opensl/SimpleAudioEngineOpenSL.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/CocosDenshion/android/opensl/OpenSLEngine.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/CocosDenshion/android/opensl/OpenSLEngine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/CocosDenshion/android/opensl/SimpleAudioEngineOpenSL.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/CocosDenshion/android/opensl/SimpleAudioEngineOpenSL.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


