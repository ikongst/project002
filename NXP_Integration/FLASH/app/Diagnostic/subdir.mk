################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/Diagnostic/Diagnostic.c" \
"../app/Diagnostic/Diagnostic_GAC.c" \
"../app/Diagnostic/Diagnostic_Geely.c" \
"../app/Diagnostic/Diagnostic_Platform.c" \

C_SRCS += \
../app/Diagnostic/Diagnostic.c \
../app/Diagnostic/Diagnostic_GAC.c \
../app/Diagnostic/Diagnostic_Geely.c \
../app/Diagnostic/Diagnostic_Platform.c \

OBJS += \
./app/Diagnostic/Diagnostic_c.obj \
./app/Diagnostic/Diagnostic_GAC_c.obj \
./app/Diagnostic/Diagnostic_Geely_c.obj \
./app/Diagnostic/Diagnostic_Platform_c.obj \

OBJS_QUOTED += \
"./app/Diagnostic/Diagnostic_c.obj" \
"./app/Diagnostic/Diagnostic_GAC_c.obj" \
"./app/Diagnostic/Diagnostic_Geely_c.obj" \
"./app/Diagnostic/Diagnostic_Platform_c.obj" \

C_DEPS += \
./app/Diagnostic/Diagnostic_c.d \
./app/Diagnostic/Diagnostic_GAC_c.d \
./app/Diagnostic/Diagnostic_Geely_c.d \
./app/Diagnostic/Diagnostic_Platform_c.d \

C_DEPS_QUOTED += \
"./app/Diagnostic/Diagnostic_c.d" \
"./app/Diagnostic/Diagnostic_GAC_c.d" \
"./app/Diagnostic/Diagnostic_Geely_c.d" \
"./app/Diagnostic/Diagnostic_Platform_c.d" \

OBJS_OS_FORMAT += \
./app/Diagnostic/Diagnostic_c.obj \
./app/Diagnostic/Diagnostic_GAC_c.obj \
./app/Diagnostic/Diagnostic_Geely_c.obj \
./app/Diagnostic/Diagnostic_Platform_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/Diagnostic/Diagnostic_c.obj: ../app/Diagnostic/Diagnostic.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Diagnostic/Diagnostic.args" -o "app/Diagnostic/Diagnostic_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/Diagnostic/%.d: ../app/Diagnostic/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

app/Diagnostic/Diagnostic_GAC_c.obj: ../app/Diagnostic/Diagnostic_GAC.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Diagnostic/Diagnostic_GAC.args" -o "app/Diagnostic/Diagnostic_GAC_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/Diagnostic/Diagnostic_Geely_c.obj: ../app/Diagnostic/Diagnostic_Geely.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Diagnostic/Diagnostic_Geely.args" -o "app/Diagnostic/Diagnostic_Geely_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/Diagnostic/Diagnostic_Platform_c.obj: ../app/Diagnostic/Diagnostic_Platform.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Diagnostic/Diagnostic_Platform.args" -o "app/Diagnostic/Diagnostic_Platform_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


