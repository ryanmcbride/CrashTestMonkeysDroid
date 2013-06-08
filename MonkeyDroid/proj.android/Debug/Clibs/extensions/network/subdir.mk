################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/network/HttpClient.cpp 

OBJS += \
./Clibs/extensions/network/HttpClient.o 

CPP_DEPS += \
./Clibs/extensions/network/HttpClient.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/extensions/network/HttpClient.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/network/HttpClient.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


