################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../LIN_Stack/lowlevel/lin.c" \

C_SRCS += \
../LIN_Stack/lowlevel/lin.c \

OBJS += \
./LIN_Stack/lowlevel/lin_c.obj \

OBJS_QUOTED += \
"./LIN_Stack/lowlevel/lin_c.obj" \

C_DEPS += \
./LIN_Stack/lowlevel/lin_c.d \

C_DEPS_QUOTED += \
"./LIN_Stack/lowlevel/lin_c.d" \

OBJS_OS_FORMAT += \
./LIN_Stack/lowlevel/lin_c.obj \


# Each subdirectory must supply rules for building sources it contributes
LIN_Stack/lowlevel/lin_c.obj: ../LIN_Stack/lowlevel/lin.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/lowlevel/lin.args" -o "LIN_Stack/lowlevel/lin_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/lowlevel/%.d: ../LIN_Stack/lowlevel/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


