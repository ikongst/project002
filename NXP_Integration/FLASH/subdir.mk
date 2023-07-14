################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../MC9S12ZVML128_PMSM.c" \
"../motorinter.c" \

C_SRCS += \
../MC9S12ZVML128_PMSM.c \
../motorinter.c \

OBJS += \
./MC9S12ZVML128_PMSM_c.obj \
./motorinter_c.obj \

OBJS_QUOTED += \
"./MC9S12ZVML128_PMSM_c.obj" \
"./motorinter_c.obj" \

C_DEPS += \
./MC9S12ZVML128_PMSM_c.d \
./motorinter_c.d \

C_DEPS_QUOTED += \
"./MC9S12ZVML128_PMSM_c.d" \
"./motorinter_c.d" \

OBJS_OS_FORMAT += \
./MC9S12ZVML128_PMSM_c.obj \
./motorinter_c.obj \


# Each subdirectory must supply rules for building sources it contributes
MC9S12ZVML128_PMSM_c.obj: ../MC9S12ZVML128_PMSM.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"MC9S12ZVML128_PMSM.args" -o "./MC9S12ZVML128_PMSM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MC9S12ZVML128_PMSM_c.d: ../MC9S12ZVML128_PMSM.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

motorinter_c.obj: ../motorinter.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"motorinter.args" -o "./motorinter_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

motorinter_c.d: ../motorinter.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


