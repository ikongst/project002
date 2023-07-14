################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/MotorOperation/MotorOperation.c" \

C_SRCS += \
../app/MotorOperation/MotorOperation.c \

OBJS += \
./app/MotorOperation/MotorOperation_c.obj \

OBJS_QUOTED += \
"./app/MotorOperation/MotorOperation_c.obj" \

C_DEPS += \
./app/MotorOperation/MotorOperation_c.d \

C_DEPS_QUOTED += \
"./app/MotorOperation/MotorOperation_c.d" \

OBJS_OS_FORMAT += \
./app/MotorOperation/MotorOperation_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/MotorOperation/MotorOperation_c.obj: ../app/MotorOperation/MotorOperation.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/MotorOperation/MotorOperation.args" -o "app/MotorOperation/MotorOperation_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/MotorOperation/%.d: ../app/MotorOperation/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


