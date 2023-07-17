################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../app/Common/Common.c" \
"../app/Common/Common_LIB.c" \
"../app/Common/TaskAnalysis.c" \

C_SRCS += \
../app/Common/Common.c \
../app/Common/Common_LIB.c \
../app/Common/TaskAnalysis.c \

OBJS += \
./app/Common/Common_c.obj \
./app/Common/Common_LIB_c.obj \
./app/Common/TaskAnalysis_c.obj \

OBJS_QUOTED += \
"./app/Common/Common_c.obj" \
"./app/Common/Common_LIB_c.obj" \
"./app/Common/TaskAnalysis_c.obj" \

C_DEPS += \
./app/Common/Common_c.d \
./app/Common/Common_LIB_c.d \
./app/Common/TaskAnalysis_c.d \

C_DEPS_QUOTED += \
"./app/Common/Common_c.d" \
"./app/Common/Common_LIB_c.d" \
"./app/Common/TaskAnalysis_c.d" \

OBJS_OS_FORMAT += \
./app/Common/Common_c.obj \
./app/Common/Common_LIB_c.obj \
./app/Common/TaskAnalysis_c.obj \


# Each subdirectory must supply rules for building sources it contributes
app/Common/Common_c.obj: ../app/Common/Common.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Common/Common.args" -o "app/Common/Common_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/Common/%.d: ../app/Common/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

app/Common/Common_LIB_c.obj: ../app/Common/Common_LIB.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Common/Common_LIB.args" -o "app/Common/Common_LIB_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

app/Common/TaskAnalysis_c.obj: ../app/Common/TaskAnalysis.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"app/Common/TaskAnalysis.args" -o "app/Common/TaskAnalysis_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


