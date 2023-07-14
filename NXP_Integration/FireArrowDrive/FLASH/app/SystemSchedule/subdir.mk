################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/SystemSchedule/SystemSchedule.c" \

C_SRCS += \
../app/SystemSchedule/SystemSchedule.c \

OBJS += \
./app/SystemSchedule/SystemSchedule_c.obj \

OBJS_QUOTED += \
"./app/SystemSchedule/SystemSchedule_c.obj" \

C_DEPS += \
./app/SystemSchedule/SystemSchedule_c.d \

C_DEPS_QUOTED += \
"./app/SystemSchedule/SystemSchedule_c.d" \

OBJS_OS_FORMAT += \
./app/SystemSchedule/SystemSchedule_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/SystemSchedule/SystemSchedule_c.obj: ../app/SystemSchedule/SystemSchedule.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/SystemSchedule/SystemSchedule.args" -o "app/SystemSchedule/SystemSchedule_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/SystemSchedule/%.d: ../app/SystemSchedule/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


