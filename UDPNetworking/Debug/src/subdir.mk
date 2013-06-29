################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConnControl.cpp \
../src/ConnControl_test.cpp \
../src/SRAU.cpp \
../src/SRAU_test.cpp \
../src/UDPHandler.cpp \
../src/UDPHandler_test.cpp \
../src/UDPNetworking.cpp 

OBJS += \
./src/ConnControl.o \
./src/ConnControl_test.o \
./src/SRAU.o \
./src/SRAU_test.o \
./src/UDPHandler.o \
./src/UDPHandler_test.o \
./src/UDPNetworking.o 

CPP_DEPS += \
./src/ConnControl.d \
./src/ConnControl_test.d \
./src/SRAU.d \
./src/SRAU_test.d \
./src/UDPHandler.d \
./src/UDPHandler_test.d \
./src/UDPNetworking.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


