################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AutoController.cpp \
../src/BaseController.cpp \
../src/DefaultEffect.cpp \
../src/EffectManager.cpp \
../src/JellyEffect.cpp \
../src/KeyboardController.cpp \
../src/KingJelly.cpp \
../src/NetworkController.cpp \
../src/RainEffect.cpp \
../src/SerialController.cpp 

OBJS += \
./src/AutoController.o \
./src/BaseController.o \
./src/DefaultEffect.o \
./src/EffectManager.o \
./src/JellyEffect.o \
./src/KeyboardController.o \
./src/KingJelly.o \
./src/NetworkController.o \
./src/RainEffect.o \
./src/SerialController.o 

CPP_DEPS += \
./src/AutoController.d \
./src/BaseController.d \
./src/DefaultEffect.d \
./src/EffectManager.d \
./src/JellyEffect.d \
./src/KeyboardController.d \
./src/KingJelly.d \
./src/NetworkController.d \
./src/RainEffect.d \
./src/SerialController.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I.. -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


