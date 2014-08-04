################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AutoController.cpp \
../src/BaseController.cpp \
../src/BaseEffect.cpp \
../src/DefaultPixelEffect.cpp \
../src/EffectManager.cpp \
../src/KingJelly.cpp \
../src/NetworkController.cpp \
../src/OriginalRainEffect.cpp \
../src/PerlinRainbow.cpp \
../src/RainEffect.cpp \
../src/SerialController.cpp 

OBJS += \
./src/AutoController.o \
./src/BaseController.o \
./src/BaseEffect.o \
./src/DefaultPixelEffect.o \
./src/EffectManager.o \
./src/KingJelly.o \
./src/NetworkController.o \
./src/OriginalRainEffect.o \
./src/PerlinRainbow.o \
./src/RainEffect.o \
./src/SerialController.o 

CPP_DEPS += \
./src/AutoController.d \
./src/BaseController.d \
./src/BaseEffect.d \
./src/DefaultPixelEffect.d \
./src/EffectManager.d \
./src/KingJelly.d \
./src/NetworkController.d \
./src/OriginalRainEffect.d \
./src/PerlinRainbow.d \
./src/RainEffect.d \
./src/SerialController.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I".." -O3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


