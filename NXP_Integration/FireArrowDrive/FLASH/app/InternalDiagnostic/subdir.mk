################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/InternalDiagnostic/InternalDiagnostic.c" \

C_SRCS += \
../app/InternalDiagnostic/InternalDiagnostic.c \

OBJS += \
./app/InternalDiagnostic/InternalDiagnostic_c.obj \

OBJS_QUOTED += \
"./app/InternalDiagnostic/InternalDiagnostic_c.obj" \

C_DEPS += \
./app/InternalDiagnostic/InternalDiagnostic_c.d \

C_DEPS_QUOTED += \
"./app/InternalDiagnostic/InternalDiagnostic_c.d" \

OBJS_OS_FORMAT += \
./app/InternalDiagnostic/InternalDiagnostic_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/InternalDiagnostic/InternalDiagnostic_c.obj: ../app/InternalDiagnostic/InternalDiagnostic.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/InternalDiagnostic/InternalDiagnostic.args" -o "app/InternalDiagnostic/InternalDiagnostic_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/InternalDiagnostic/%.d: ../app/InternalDiagnostic/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


