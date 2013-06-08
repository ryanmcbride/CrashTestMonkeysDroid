################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/zip_support/ZipUtils.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/zip_support/ioapi.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/zip_support/unzip.cpp 

OBJS += \
./Clibs/cocos2dx/support/zip_support/ZipUtils.o \
./Clibs/cocos2dx/support/zip_support/ioapi.o \
./Clibs/cocos2dx/support/zip_support/unzip.o 

CPP_DEPS += \
./Clibs/cocos2dx/support/zip_support/ZipUtils.d \
./Clibs/cocos2dx/support/zip_support/ioapi.d \
./Clibs/cocos2dx/support/zip_support/unzip.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/support/zip_support/ZipUtils.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/zip_support/ZipUtils.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/support/zip_support/ioapi.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/zip_support/ioapi.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/support/zip_support/unzip.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/support/zip_support/unzip.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


