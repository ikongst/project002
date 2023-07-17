################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/Measurement/Measurement.c" \
"../app/Measurement/NTC.c" \

C_SRCS += \
../app/Measurement/Measurement.c \
../app/Measurement/NTC.c \

OBJS += \
./app/Measurement/Measurement_c.obj \
./app/Measurement/NTC_c.obj \

OBJS_QUOTED += \
"./app/Measurement/Measurement_c.obj" \
"./app/Measurement/NTC_c.obj" \

C_DEPS += \
./app/Measurement/Measurement_c.d \
./app/Measurement/NTC_c.d \

C_DEPS_QUOTED += \
"./app/Measurement/Measurement_c.d" \
"./app/Measurement/NTC_c.d" \

OBJS_OS_FORMAT += \
./app/Measurement/Measurement_c.obj \
./app/Measurement/NTC_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/Measurement/Measurement_c.obj: ../app/Measurement/Measurement.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Measurement/Measurement.args" -o "app/Measurement/Measurement_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/Measurement/%.d: ../app/Measurement/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

app/Measurement/NTC_c.obj: ../app/Measurement/NTC.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Measurement/NTC.args" -o "app/Measurement/NTC_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


