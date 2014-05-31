################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DefaultEffect.cpp \
../src/EffectManager.cpp \
../src/JellyEffect.cpp \
../src/KeyboardController.cpp \
../src/KingJelly.cpp \
../src/NetworkController.cpp \
../src/RainEffect.cpp 

OBJS += \
./src/DefaultEffect.o \
./src/EffectManager.o \
./src/JellyEffect.o \
./src/KeyboardController.o \
./src/KingJelly.o \
./src/NetworkController.o \
./src/RainEffect.o 

CPP_DEPS += \
./src/DefaultEffect.d \
./src/EffectManager.d \
./src/JellyEffect.d \
./src/KeyboardController.d \
./src/KingJelly.d \
./src/NetworkController.d \
./src/RainEffect.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I.. -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


