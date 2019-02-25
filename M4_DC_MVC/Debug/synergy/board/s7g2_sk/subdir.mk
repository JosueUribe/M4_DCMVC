################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/board/s7g2_sk/bsp_init.c \
../synergy/board/s7g2_sk/bsp_leds.c \
../synergy/board/s7g2_sk/bsp_qspi.c 

OBJS += \
./synergy/board/s7g2_sk/bsp_init.o \
./synergy/board/s7g2_sk/bsp_leds.o \
./synergy/board/s7g2_sk/bsp_qspi.o 

C_DEPS += \
./synergy/board/s7g2_sk/bsp_init.d \
./synergy/board/s7g2_sk/bsp_leds.d \
./synergy/board/s7g2_sk/bsp_qspi.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/board/s7g2_sk/%.o: ../synergy/board/s7g2_sk/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\Synergy\e2studio_v6.2.1_ssp_v1.5.0-rc1\eclipse\/../\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\driver" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\bsp" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\driver\api" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\driver\instances" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\src" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\src\synergy_gen" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\el" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\src\framework\el\tx" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy_cfg\ssp_cfg\framework" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\api" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\instances" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\src\framework\el\ux" -I"C:\Users\uribe\Documents\Files\CESEQ\M4_DCMVC\M4_DCMVC\M4_DC_MVC\synergy\ssp\inc\framework\tes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


