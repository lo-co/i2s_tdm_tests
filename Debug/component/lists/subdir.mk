################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/fsl_component_generic_list.c 

C_DEPS += \
./component/lists/fsl_component_generic_list.d 

OBJS += \
./component/lists/fsl_component_generic_list.o 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c component/lists/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT685SFVKB -DCPU_MIMXRT685SFVKB_cm33 -DBOOT_HEADER_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DMCUXPRESSO_SDK -DCODEC_CS42448_ENABLE -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/source" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/component/i2c" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/codec" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/utilities" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/codec/port/cs42448" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/codec/port" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/drivers" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/device" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/component/uart" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/flash_config" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/component/lists" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/MIMXRT685S" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/CMSIS" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/board" -I"/home/mrichardson/rt685_workspace/i2s_tdm_test/mimxrt685audevk/driver_examples/i2s/dma_tdm_record_playback" -O0 -fno-common -g3 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/fsl_component_generic_list.d ./component/lists/fsl_component_generic_list.o

.PHONY: clean-component-2f-lists

