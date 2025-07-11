# === Paths ===
TIVAWARE_PATH ?= C:\ti\TivaWare_C_Series-2.2.0.295\inc\*# Path to Tivaware Library
TOOLCHAIN_PATH ?= C:\tools\gcc-arm-none-eabi-10.3-2021.10\bin# Path to ARM GCC Toolchain
LD_PATH ?= tiva_board_driver.ld# Path to linker script
CMSIS_PATH ?= C:\Users\Yella_Nikhil\AppData\Local\Arm\Packs\Keil\TM4C_DFP\1.1.0\Device\Include\TM4C123
CMSIS_CORE_PATH ?= C:\Users\Yella_Nikhil\AppData\Local\Arm\Packs\ARM\CMSIS\6.1.0\CMSIS\Core\Include

# === Toolchain Binaries ===
CC := $(TOOLCHAIN_PATH)\arm-none-eabi-gcc
LD := $(TOOLCHAIN_PATH)\arm-none-eabi-gcc
OBJCOPY := $(TOOLCHAIN_PATH)\arm-none-eabi-objcopy
OBJDUMP := $(TOOLCHAIN_PATH)\arm-none-eabi-objdump
SIZE := $(TOOLCHAIN_PATH)\arm-none-eabi-size

# === Project Info ===
TARGET := tiva_board_drivers
BUILD_DIR := build
SRC_DIR := src
MCU = cortex-m4

# === Source Files ===
SRCS := $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# === Includes ===
INCLUDES := -I$(SRC_DIR) -I$(CMSIS_PATH) -I$(CMSIS_CORE_PATH) -Iincludes -IRTE/Device/TM4C123GH6PM

# === Compiler/Linker Flags ===
# CFLAGS := -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Wall -O2 -ffreestanding -nostdlib $(INCLUDES)
CFLAGS = -mcpu=$(MCU) -mthumb -Os -ffunction-sections -fdata-sections -std=c99 -Wall
CFLAGS += -I $(INCLUDES) -DPART_TM4C123GH6PM
LDFLAGS := -T$(LD_PATH) -nostdlib -Wl,-Map=$(TARGET).map -Wl,--gc-sections

# === Targets ===

all: $(BUILD_DIR) $(TARGET).bin

# Create build directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Object file generation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

# ELF generation
$(TARGET).elf: $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	$(OBJDUMP) -D $< > $(TARGET).lst

# Convert to binary
bin: all
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# Flash with OpenOCD (make sure config is correct)
flash: bin
	openocd -f interface/cmsis-dap.cfg -f target/stellaris.cfg -c "program $(BUILD_DIR)/$(TARGET).bin verify reset exit 0x00000000"

# Disassemble
disasm:
	$(OBJDUMP) -D $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).lst

clean:
	del /Q /F $(BUILD_DIR)\*.o 2> NUL || true
	del /Q /F *.elf *.bin *.lst *.map 2> NUL || true

.PHONY: all clean bin flash disasm
