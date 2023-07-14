################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/ProjectConfig/ProjectConfig.c" \

C_SRCS += \
../app/ProjectConfig/ProjectConfig.c \

OBJS += \
./app/ProjectConfig/ProjectConfig_c.obj \

OBJS_QUOTED += \
"./app/ProjectConfig/ProjectConfig_c.obj" \

C_DEPS += \
./app/ProjectConfig/ProjectConfig_c.d \

C_DEPS_QUOTED += \
"./app/ProjectConfig/ProjectConfig_c.d" \

OBJS_OS_FORMAT += \
./app/ProjectConfig/ProjectConfig_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/ProjectConfig/ProjectConfig_c.obj: ../app/ProjectConfig/ProjectConfig.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/ProjectConfig/ProjectConfig.args" -o "app/ProjectConfig/ProjectConfig_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/ProjectConfig/%.d: ../app/ProjectConfig/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


