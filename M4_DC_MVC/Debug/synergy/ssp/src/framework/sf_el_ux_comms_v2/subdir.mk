################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/framework/sf_el_ux_comms_v2/sf_el_ux_comms.c 

OBJS += \
./synergy/ssp/src/framework/sf_el_ux_comms_v2/sf_el_ux_comms.o 

C_DEPS += \
./synergy/ssp/src/framework/sf_el_ux_comms_v2/sf_el_ux_comms.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/framework/sf_el_ux_comms_v2/%.o: ../synergy/ssp/src/framework/sf_el_ux_comms_v2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\Synergy\e2studio_v6.2.1_ssp_v1.5.0-rc1\eclipse\/../\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\driver" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\bsp" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\driver\api" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\driver\instances" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\src" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\src\synergy_gen" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\el" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\src\framework\el\tx" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\framework" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\api" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\instances" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\src\framework\el\ux" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\tes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


