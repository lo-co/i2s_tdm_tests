################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include source/subdir.mk
-include flash_config/subdir.mk
-include drivers/subdir.mk
-include component/uart/subdir.mk
-include component/lists/subdir.mk
-include component/i2c/subdir.mk
-include codec/port/cs42448/subdir.mk
-include codec/subdir.mk
-include board/subdir.mk
-include MIMXRT685S/mcuxpresso/subdir.mk
-include MIMXRT685S/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := mimxrt685audevk_i2s_dma_tdm_record_playback
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: mimxrt685audevk_i2s_dma_tdm_record_playback.axf

# Tool invocations
mimxrt685audevk_i2s_dma_tdm_record_playback.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -no-warn-rwx-segments -Xlinker -Map="mimxrt685audevk_i2s_dma_tdm_record_playback.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T mimxrt685audevk_i2s_dma_tdm_record_playback_Debug.ld -o "mimxrt685audevk_i2s_dma_tdm_record_playback.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) mimxrt685audevk_i2s_dma_tdm_record_playback.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "mimxrt685audevk_i2s_dma_tdm_record_playback.axf"; # arm-none-eabi-objcopy -v -O binary "mimxrt685audevk_i2s_dma_tdm_record_playback.axf" "mimxrt685audevk_i2s_dma_tdm_record_playback.bin" ; # checksum -p MIMXRT685S -d "mimxrt685audevk_i2s_dma_tdm_record_playback.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
