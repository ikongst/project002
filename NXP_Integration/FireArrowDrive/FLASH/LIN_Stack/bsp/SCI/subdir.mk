################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../LIN_Stack/bsp/SCI/lin_isr.c" \
"../LIN_Stack/bsp/SCI/lin_lld_sci.c" \
"../LIN_Stack/bsp/SCI/lin_lld_timesrv.c" \

C_SRCS += \
../LIN_Stack/bsp/SCI/lin_isr.c \
../LIN_Stack/bsp/SCI/lin_lld_sci.c \
../LIN_Stack/bsp/SCI/lin_lld_timesrv.c \

OBJS += \
./LIN_Stack/bsp/SCI/lin_isr_c.obj \
./LIN_Stack/bsp/SCI/lin_lld_sci_c.obj \
./LIN_Stack/bsp/SCI/lin_lld_timesrv_c.obj \

OBJS_QUOTED += \
"./LIN_Stack/bsp/SCI/lin_isr_c.obj" \
"./LIN_Stack/bsp/SCI/lin_lld_sci_c.obj" \
"./LIN_Stack/bsp/SCI/lin_lld_timesrv_c.obj" \

C_DEPS += \
./LIN_Stack/bsp/SCI/lin_isr_c.d \
./LIN_Stack/bsp/SCI/lin_lld_sci_c.d \
./LIN_Stack/bsp/SCI/lin_lld_timesrv_c.d \

C_DEPS_QUOTED += \
"./LIN_Stack/bsp/SCI/lin_isr_c.d" \
"./LIN_Stack/bsp/SCI/lin_lld_sci_c.d" \
"./LIN_Stack/bsp/SCI/lin_lld_timesrv_c.d" \

OBJS_OS_FORMAT += \
./LIN_Stack/bsp/SCI/lin_isr_c.obj \
./LIN_Stack/bsp/SCI/lin_lld_sci_c.obj \
./LIN_Stack/bsp/SCI/lin_lld_timesrv_c.obj \


# Each subdirectory must supply rules for building sources it contributes
LIN_Stack/bsp/SCI/lin_isr_c.obj: ../LIN_Stack/bsp/SCI/lin_isr.c
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/bsp/SCI/lin_isr.args" -o "LIN_Stack/bsp/SCI/lin_isr_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/bsp/SCI/%.d: ../LIN_Stack/bsp/SCI/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

LIN_Stack/bsp/SCI/lin_lld_sci_c.obj: ../LIN_Stack/bsp/SCI/lin_lld_sci.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/bsp/SCI/lin_lld_sci.args" -o "LIN_Stack/bsp/SCI/lin_lld_sci_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/bsp/SCI/lin_lld_timesrv_c.obj: ../LIN_Stack/bsp/SCI/lin_lld_timesrv.c
	@echo 'Building file: $<'
	@echo 'Executing target #59 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/bsp/SCI/lin_lld_timesrv.args" -o "LIN_Stack/bsp/SCI/lin_lld_timesrv_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


