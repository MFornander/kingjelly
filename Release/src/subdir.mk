################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DefaultEffect.cpp \
../src/RainEffect.cpp \
../src/EffectManager.cpp \
../src/IState.cpp \
../src/KeyboardState.cpp \
../src/NetworkState.cpp \
../src/KingJelly.cpp 

OBJS += \
./src/DefaultEffect.o \
./src/RainEffect.o \
./src/EffectManager.o \
./src/IState.o \
./src/KeyboardState.o \
./src/NetworkState.o \
./src/KingJelly.o 

CPP_DEPS += \
./src/DefaultEffect.d \
./src/RainEffect.d \
./src/EffectManager.d \
./src/IState.d \
./src/KeyboardState.d \
./src/NetworkState.d \
./src/KingJelly.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I.. -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


