################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../LIN_Stack/coreapi/lin_common_api.c" \
"../LIN_Stack/coreapi/lin_common_proto.c" \
"../LIN_Stack/coreapi/lin_j2602_api.c" \
"../LIN_Stack/coreapi/lin_j2602_proto.c" \
"../LIN_Stack/coreapi/lin_lin21_api.c" \
"../LIN_Stack/coreapi/lin_lin21_proto.c" \

C_SRCS += \
../LIN_Stack/coreapi/lin_common_api.c \
../LIN_Stack/coreapi/lin_common_proto.c \
../LIN_Stack/coreapi/lin_j2602_api.c \
../LIN_Stack/coreapi/lin_j2602_proto.c \
../LIN_Stack/coreapi/lin_lin21_api.c \
../LIN_Stack/coreapi/lin_lin21_proto.c \

OBJS += \
./LIN_Stack/coreapi/lin_common_api_c.obj \
./LIN_Stack/coreapi/lin_common_proto_c.obj \
./LIN_Stack/coreapi/lin_j2602_api_c.obj \
./LIN_Stack/coreapi/lin_j2602_proto_c.obj \
./LIN_Stack/coreapi/lin_lin21_api_c.obj \
./LIN_Stack/coreapi/lin_lin21_proto_c.obj \

OBJS_QUOTED += \
"./LIN_Stack/coreapi/lin_common_api_c.obj" \
"./LIN_Stack/coreapi/lin_common_proto_c.obj" \
"./LIN_Stack/coreapi/lin_j2602_api_c.obj" \
"./LIN_Stack/coreapi/lin_j2602_proto_c.obj" \
"./LIN_Stack/coreapi/lin_lin21_api_c.obj" \
"./LIN_Stack/coreapi/lin_lin21_proto_c.obj" \

C_DEPS += \
./LIN_Stack/coreapi/lin_common_api_c.d \
./LIN_Stack/coreapi/lin_common_proto_c.d \
./LIN_Stack/coreapi/lin_j2602_api_c.d \
./LIN_Stack/coreapi/lin_j2602_proto_c.d \
./LIN_Stack/coreapi/lin_lin21_api_c.d \
./LIN_Stack/coreapi/lin_lin21_proto_c.d \

C_DEPS_QUOTED += \
"./LIN_Stack/coreapi/lin_common_api_c.d" \
"./LIN_Stack/coreapi/lin_common_proto_c.d" \
"./LIN_Stack/coreapi/lin_j2602_api_c.d" \
"./LIN_Stack/coreapi/lin_j2602_proto_c.d" \
"./LIN_Stack/coreapi/lin_lin21_api_c.d" \
"./LIN_Stack/coreapi/lin_lin21_proto_c.d" \

OBJS_OS_FORMAT += \
./LIN_Stack/coreapi/lin_common_api_c.obj \
./LIN_Stack/coreapi/lin_common_proto_c.obj \
./LIN_Stack/coreapi/lin_j2602_api_c.obj \
./LIN_Stack/coreapi/lin_j2602_proto_c.obj \
./LIN_Stack/coreapi/lin_lin21_api_c.obj \
./LIN_Stack/coreapi/lin_lin21_proto_c.obj \


# Each subdirectory must supply rules for building sources it contributes
LIN_Stack/coreapi/lin_common_api_c.obj: ../LIN_Stack/coreapi/lin_common_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/coreapi/lin_common_api.args" -o "LIN_Stack/coreapi/lin_common_api_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/coreapi/%.d: ../LIN_Stack/coreapi/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

LIN_Stack/coreapi/lin_common_proto_c.obj: ../LIN_Stack/coreapi/lin_common_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/coreapi/lin_common_proto.args" -o "LIN_Stack/coreapi/lin_common_proto_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/coreapi/lin_j2602_api_c.obj: ../LIN_Stack/coreapi/lin_j2602_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/coreapi/lin_j2602_api.args" -o "LIN_Stack/coreapi/lin_j2602_api_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/coreapi/lin_j2602_proto_c.obj: ../LIN_Stack/coreapi/lin_j2602_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/coreapi/lin_j2602_proto.args" -o "LIN_Stack/coreapi/lin_j2602_proto_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/coreapi/lin_lin21_api_c.obj: ../LIN_Stack/coreapi/lin_lin21_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/coreapi/lin_lin21_api.args" -o "LIN_Stack/coreapi/lin_lin21_api_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/coreapi/lin_lin21_proto_c.obj: ../LIN_Stack/coreapi/lin_lin21_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/coreapi/lin_lin21_proto.args" -o "LIN_Stack/coreapi/lin_lin21_proto_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


