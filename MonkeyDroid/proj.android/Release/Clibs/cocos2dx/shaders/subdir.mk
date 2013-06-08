################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/CCGLProgram.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/CCShaderCache.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/ccGLStateCache.cpp \
/Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/ccShaders.cpp 

OBJS += \
./Clibs/cocos2dx/shaders/CCGLProgram.o \
./Clibs/cocos2dx/shaders/CCShaderCache.o \
./Clibs/cocos2dx/shaders/ccGLStateCache.o \
./Clibs/cocos2dx/shaders/ccShaders.o 

CPP_DEPS += \
./Clibs/cocos2dx/shaders/CCGLProgram.d \
./Clibs/cocos2dx/shaders/CCShaderCache.d \
./Clibs/cocos2dx/shaders/ccGLStateCache.d \
./Clibs/cocos2dx/shaders/ccShaders.d 


# Each subdirectory must supply rules for building sources it contributes
Clibs/cocos2dx/shaders/CCGLProgram.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/CCGLProgram.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/shaders/CCShaderCache.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/CCShaderCache.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/shaders/ccGLStateCache.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/ccGLStateCache.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Clibs/cocos2dx/shaders/ccShaders.o: /Users/administrator/Desktop/depot/MonkeyDroid/MonkeyDroid/libs/cocos2dx/shaders/ccShaders.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


