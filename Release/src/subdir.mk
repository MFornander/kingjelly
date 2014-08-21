################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AutoController.cpp \
../src/BaseController.cpp \
../src/BaseEffect.cpp \
../src/EffectManager.cpp \
../src/EffectMattias.cpp \
../src/KingJelly.cpp \
../src/NetworkController.cpp \
../src/OriginalRainEffect.cpp \
../src/RainEffect.cpp \
../src/RotatingWaveEffect.cpp \
../src/SerialController.cpp \
../src/SparkleMotionEffect.cpp \
../src/SpiralEffect.cpp 

OBJS += \
./src/AutoController.o \
./src/BaseController.o \
./src/BaseEffect.o \
./src/EffectManager.o \
./src/EffectMattias.o \
./src/KingJelly.o \
./src/NetworkController.o \
./src/OriginalRainEffect.o \
./src/RainEffect.o \
./src/RotatingWaveEffect.o \
./src/SerialController.o \
./src/SparkleMotionEffect.o \
./src/SpiralEffect.o 

CPP_DEPS += \
./src/AutoController.d \
./src/BaseController.d \
./src/BaseEffect.d \
./src/EffectManager.d \
./src/EffectMattias.d \
./src/KingJelly.d \
./src/NetworkController.d \
./src/OriginalRainEffect.d \
./src/RainEffect.d \
./src/RotatingWaveEffect.d \
./src/SerialController.d \
./src/SparkleMotionEffect.d \
./src/SpiralEffect.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I".." -O3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


