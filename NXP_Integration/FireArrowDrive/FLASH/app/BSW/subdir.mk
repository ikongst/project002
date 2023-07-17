################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/BSW/BSW.c" \

C_SRCS += \
../app/BSW/BSW.c \

OBJS += \
./app/BSW/BSW_c.obj \

OBJS_QUOTED += \
"./app/BSW/BSW_c.obj" \

C_DEPS += \
./app/BSW/BSW_c.d \

C_DEPS_QUOTED += \
"./app/BSW/BSW_c.d" \

OBJS_OS_FORMAT += \
./app/BSW/BSW_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/BSW/BSW_c.obj: ../app/BSW/BSW.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/BSW/BSW.args" -o "app/BSW/BSW_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/BSW/%.d: ../app/BSW/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


