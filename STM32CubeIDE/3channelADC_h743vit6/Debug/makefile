################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
3channelADC_h743vit6.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
3channelADC_h743vit6.list \

OBJCOPY_BIN += \
3channelADC_h743vit6.bin \


# All Target
all: 3channelADC_h743vit6.elf secondary-outputs

# Tool invocations
3channelADC_h743vit6.elf: $(OBJS) $(USER_OBJS) F:\CytomertGetDataSystem\New_4PI_CYTOMETR\STM32CubeIDE\3channelADC_h743vit6\STM32H743VITX_FLASH.ld
	arm-none-eabi-gcc -o "3channelADC_h743vit6.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"F:\CytomertGetDataSystem\New_4PI_CYTOMETR\STM32CubeIDE\3channelADC_h743vit6\STM32H743VITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="3channelADC_h743vit6.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

3channelADC_h743vit6.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "3channelADC_h743vit6.list"
	@echo 'Finished building: $@'
	@echo ' '

3channelADC_h743vit6.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "3channelADC_h743vit6.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
