################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc_thread_entry.c \
../src/blinky_thread_entry.c \
../src/diagnostics_thread_entry.c \
../src/guiapp_event_handlers.c \
../src/hal_entry.c \
../src/hall_effect_thread_entry.c \
../src/main_thread_entry.c \
../src/pwm_thread_entry.c \
../src/usb_console_thread_entry.c 

OBJS += \
./src/adc_thread_entry.o \
./src/blinky_thread_entry.o \
./src/diagnostics_thread_entry.o \
./src/guiapp_event_handlers.o \
./src/hal_entry.o \
./src/hall_effect_thread_entry.o \
./src/main_thread_entry.o \
./src/pwm_thread_entry.o \
./src/usb_console_thread_entry.o 

C_DEPS += \
./src/adc_thread_entry.d \
./src/blinky_thread_entry.d \
./src/diagnostics_thread_entry.d \
./src/guiapp_event_handlers.d \
./src/hal_entry.d \
./src/hall_effect_thread_entry.d \
./src/main_thread_entry.d \
./src/pwm_thread_entry.d \
./src/usb_console_thread_entry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\Synergy\e2studio_v6.2.1_ssp_v1.5.0-rc1\eclipse\/../\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\driver" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\bsp" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\driver\api" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\driver\instances" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\src" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\src\synergy_gen" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\el" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\src\framework\el\tx" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\framework" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\api" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\instances" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\src\framework\el\ux" -I"C:\Users\VictorOmar\Desktop\Diplomado en SW embebido\Repositorio_Proyecto_Integrador\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\tes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


