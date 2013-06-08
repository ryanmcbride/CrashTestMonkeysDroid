################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/LocalStorage/LocalStorage.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/LocalStorage/LocalStorageAndroid.cpp 

OBJS += \
./Clibs/extensions/LocalStorage/LocalStorage.o \
./Clibs/extensions/LocalStorage/LocalStorageAndroid.o 

CPP_DEPS += \
./Clibs/extensions/LocalStorage/LocalStorage.d \
./Clibs/extensions/LocalStorage/LocalStorageAndroid.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/extensions/LocalStorage/LocalStorage.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/LocalStorage/LocalStorage.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/extensions/LocalStorage/LocalStorageAndroid.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/LocalStorage/LocalStorageAndroid.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


