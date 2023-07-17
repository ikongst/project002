################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../LIN_Stack/diagnostic/lin_diagnostic_service.c" \

C_SRCS += \
../LIN_Stack/diagnostic/lin_diagnostic_service.c \

OBJS += \
./LIN_Stack/diagnostic/lin_diagnostic_service_c.obj \

OBJS_QUOTED += \
"./LIN_Stack/diagnostic/lin_diagnostic_service_c.obj" \

C_DEPS += \
./LIN_Stack/diagnostic/lin_diagnostic_service_c.d \

C_DEPS_QUOTED += \
"./LIN_Stack/diagnostic/lin_diagnostic_service_c.d" \

OBJS_OS_FORMAT += \
./LIN_Stack/diagnostic/lin_diagnostic_service_c.obj \


# Each subdirectory must supply rules for building sources it contributes
LIN_Stack/diagnostic/lin_diagnostic_service_c.obj: ../LIN_Stack/diagnostic/lin_diagnostic_service.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/diagnostic/lin_diagnostic_service.args" -o "LIN_Stack/diagnostic/lin_diagnostic_service_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/diagnostic/%.d: ../LIN_Stack/diagnostic/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


