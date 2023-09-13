################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/i2c/fsl_adapter_flexcomm_i2c.c 

C_DEPS += \
./component/i2c/fsl_adapter_flexcomm_i2c.d 

OBJS += \
./component/i2c/fsl_adapter_flexcomm_i2c.o 


# Each subdirectory must supply rules for building sources it contributes
component/i2c/%.o: ../component/i2c/%.c component/i2c/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT685SFVKB -DCPU_MIMXRT685SFVKB_cm33 -DBOOT_HEADER_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DMCUXPRESSO_SDK -DCODEC_CS42448_ENABLE -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/source" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/component/i2c" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/codec" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/utilities" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/codec/port/cs42448" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/codec/port" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/drivers" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/device" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/component/uart" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/flash_config" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/component/lists" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/MIMXRT685S" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/CMSIS" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/board" -I"/home/mrichardson/rt685_workspace/mimxrt685audevk_i2s_dma_tdm_record_playback/mimxrt685audevk/driver_examples/i2s/dma_tdm_record_playback" -O0 -fno-common -g3 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-i2c

clean-component-2f-i2c:
	-$(RM) ./component/i2c/fsl_adapter_flexcomm_i2c.d ./component/i2c/fsl_adapter_flexcomm_i2c.o

.PHONY: clean-component-2f-i2c

