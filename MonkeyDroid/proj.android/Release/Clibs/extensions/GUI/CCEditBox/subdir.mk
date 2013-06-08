################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/GUI/CCEditBox/CCEditBox.cpp 

OBJS += \
./Clibs/extensions/GUI/CCEditBox/CCEditBox.o 

CPP_DEPS += \
./Clibs/extensions/GUI/CCEditBox/CCEditBox.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/extensions/GUI/CCEditBox/CCEditBox.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/extensions/GUI/CCEditBox/CCEditBox.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


