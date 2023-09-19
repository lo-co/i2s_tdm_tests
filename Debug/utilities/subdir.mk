################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

S_UPPER_SRCS += \
../utilities/fsl_memcpy.S 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_memcpy.o \
./utilities/fsl_str.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT685SFVKB -DCPU_MIMXRT685SFVKB_cm33 -DBOOT_HEADER_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DMCUXPRESSO_SDK -DCODEC_CS42448_ENABLE -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/source" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/component/i2c" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/codec" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/utilities" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/codec/port/cs42448" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/codec/port" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/drivers" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/device" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/component/uart" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/flash_config" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/component/lists" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/MIMXRT685S" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/CMSIS" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/board" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/mimxrt685audevk/driver_examples/i2s/dma_tdm_record_playback" -O0 -fno-common -g3 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/%.o: ../utilities/%.S utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/source" -g3 -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o ./utilities/fsl_memcpy.o ./utilities/fsl_str.d ./utilities/fsl_str.o

.PHONY: clean-utilities

