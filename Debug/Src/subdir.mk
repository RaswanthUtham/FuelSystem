################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/app_gpio.c \
../Src/app_lcd.c \
../Src/arm_cm4.c \
../Src/main.c \
../Src/stm32f4xx_app_irq.c \
../Src/stm32f4xx_hal_port.c \
../Src/stm32f4xx_hal_spi.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/app_gpio.o \
./Src/app_lcd.o \
./Src/arm_cm4.o \
./Src/main.o \
./Src/stm32f4xx_app_irq.o \
./Src/stm32f4xx_hal_port.o \
./Src/stm32f4xx_hal_spi.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/app_gpio.d \
./Src/app_lcd.d \
./Src/arm_cm4.d \
./Src/main.d \
./Src/stm32f4xx_app_irq.d \
./Src/stm32f4xx_hal_port.d \
./Src/stm32f4xx_hal_spi.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F466RE -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/app_gpio.cyclo ./Src/app_gpio.d ./Src/app_gpio.o ./Src/app_gpio.su ./Src/app_lcd.cyclo ./Src/app_lcd.d ./Src/app_lcd.o ./Src/app_lcd.su ./Src/arm_cm4.cyclo ./Src/arm_cm4.d ./Src/arm_cm4.o ./Src/arm_cm4.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32f4xx_app_irq.cyclo ./Src/stm32f4xx_app_irq.d ./Src/stm32f4xx_app_irq.o ./Src/stm32f4xx_app_irq.su ./Src/stm32f4xx_hal_port.cyclo ./Src/stm32f4xx_hal_port.d ./Src/stm32f4xx_hal_port.o ./Src/stm32f4xx_hal_port.su ./Src/stm32f4xx_hal_spi.cyclo ./Src/stm32f4xx_hal_spi.d ./Src/stm32f4xx_hal_spi.o ./Src/stm32f4xx_hal_spi.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

