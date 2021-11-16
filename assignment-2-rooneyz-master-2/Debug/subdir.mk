################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chambers_20th_century_dictionary.c \
../dictionary.c \
../test_dictionary.c 

OBJS += \
./chambers_20th_century_dictionary.o \
./dictionary.o \
./test_dictionary.o 

C_DEPS += \
./chambers_20th_century_dictionary.d \
./dictionary.d \
./test_dictionary.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


