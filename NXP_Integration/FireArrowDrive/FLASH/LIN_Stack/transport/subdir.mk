################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../LIN_Stack/transport/lin_commontl_api.c" \
"../LIN_Stack/transport/lin_commontl_proto.c" \
"../LIN_Stack/transport/lin_j2602tl_api.c" \
"../LIN_Stack/transport/lin_lin21tl_api.c" \

C_SRCS += \
../LIN_Stack/transport/lin_commontl_api.c \
../LIN_Stack/transport/lin_commontl_proto.c \
../LIN_Stack/transport/lin_j2602tl_api.c \
../LIN_Stack/transport/lin_lin21tl_api.c \

OBJS += \
./LIN_Stack/transport/lin_commontl_api_c.obj \
./LIN_Stack/transport/lin_commontl_proto_c.obj \
./LIN_Stack/transport/lin_j2602tl_api_c.obj \
./LIN_Stack/transport/lin_lin21tl_api_c.obj \

OBJS_QUOTED += \
"./LIN_Stack/transport/lin_commontl_api_c.obj" \
"./LIN_Stack/transport/lin_commontl_proto_c.obj" \
"./LIN_Stack/transport/lin_j2602tl_api_c.obj" \
"./LIN_Stack/transport/lin_lin21tl_api_c.obj" \

C_DEPS += \
./LIN_Stack/transport/lin_commontl_api_c.d \
./LIN_Stack/transport/lin_commontl_proto_c.d \
./LIN_Stack/transport/lin_j2602tl_api_c.d \
./LIN_Stack/transport/lin_lin21tl_api_c.d \

C_DEPS_QUOTED += \
"./LIN_Stack/transport/lin_commontl_api_c.d" \
"./LIN_Stack/transport/lin_commontl_proto_c.d" \
"./LIN_Stack/transport/lin_j2602tl_api_c.d" \
"./LIN_Stack/transport/lin_lin21tl_api_c.d" \

OBJS_OS_FORMAT += \
./LIN_Stack/transport/lin_commontl_api_c.obj \
./LIN_Stack/transport/lin_commontl_proto_c.obj \
./LIN_Stack/transport/lin_j2602tl_api_c.obj \
./LIN_Stack/transport/lin_lin21tl_api_c.obj \


# Each subdirectory must supply rules for building sources it contributes
LIN_Stack/transport/lin_commontl_api_c.obj: ../LIN_Stack/transport/lin_commontl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/transport/lin_commontl_api.args" -o "LIN_Stack/transport/lin_commontl_api_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/transport/%.d: ../LIN_Stack/transport/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

LIN_Stack/transport/lin_commontl_proto_c.obj: ../LIN_Stack/transport/lin_commontl_proto.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/transport/lin_commontl_proto.args" -o "LIN_Stack/transport/lin_commontl_proto_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/transport/lin_j2602tl_api_c.obj: ../LIN_Stack/transport/lin_j2602tl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/transport/lin_j2602tl_api.args" -o "LIN_Stack/transport/lin_j2602tl_api_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/transport/lin_lin21tl_api_c.obj: ../LIN_Stack/transport/lin_lin21tl_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/transport/lin_lin21tl_api.args" -o "LIN_Stack/transport/lin_lin21tl_api_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


