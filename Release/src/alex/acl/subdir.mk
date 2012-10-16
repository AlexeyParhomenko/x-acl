################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/alex/acl/Group.cpp \
../src/alex/acl/Parse.cpp \
../src/alex/acl/ParseException.cpp \
../src/alex/acl/Rule.cpp \
../src/alex/acl/Rules.cpp 

OBJS += \
./src/alex/acl/Group.o \
./src/alex/acl/Parse.o \
./src/alex/acl/ParseException.o \
./src/alex/acl/Rule.o \
./src/alex/acl/Rules.o 

CPP_DEPS += \
./src/alex/acl/Group.d \
./src/alex/acl/Parse.d \
./src/alex/acl/ParseException.d \
./src/alex/acl/Rule.d \
./src/alex/acl/Rules.d 


# Each subdirectory must supply rules for building sources it contributes
src/alex/acl/%.o: ../src/alex/acl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


