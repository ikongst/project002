################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Lib/mc9s12zvml128.c" \

C_SRCS += \
../Lib/mc9s12zvml128.c \

OBJS += \
./Lib/mc9s12zvml128_c.obj \

OBJS_QUOTED += \
"./Lib/mc9s12zvml128_c.obj" \

C_DEPS += \
./Lib/mc9s12zvml128_c.d \

C_DEPS_QUOTED += \
"./Lib/mc9s12zvml128_c.d" \

OBJS_OS_FORMAT += \
./Lib/mc9s12zvml128_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Lib/mc9s12zvml128_c.obj: ../Lib/mc9s12zvml128.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Lib/mc9s12zvml128.args" -o "Lib/mc9s12zvml128_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Lib/%.d: ../Lib/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


