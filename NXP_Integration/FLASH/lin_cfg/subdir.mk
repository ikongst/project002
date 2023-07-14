################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../lin_cfg/lin_cfg.c" \

C_SRCS += \
../lin_cfg/lin_cfg.c \

OBJS += \
./lin_cfg/lin_cfg_c.obj \

OBJS_QUOTED += \
"./lin_cfg/lin_cfg_c.obj" \

C_DEPS += \
./lin_cfg/lin_cfg_c.d \

C_DEPS_QUOTED += \
"./lin_cfg/lin_cfg_c.d" \

OBJS_OS_FORMAT += \
./lin_cfg/lin_cfg_c.obj \


# Each subdirectory must supply rules for building sources it contributes
lin_cfg/lin_cfg_c.obj: ../lin_cfg/lin_cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"lin_cfg/lin_cfg.args" -o "lin_cfg/lin_cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

lin_cfg/%.d: ../lin_cfg/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


