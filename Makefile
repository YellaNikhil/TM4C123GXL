# === Project Info ===
TARGET := tiva_board_drivers
BUILD_DIR := build
SRC_DIR := src
MCU = cortex-m4
RM := rm -rf
MKDIR = mkdir -p $(dir $@)

#DEV : your TM4C123GH6PM when connected to your system, usually will be /dev/ttyACM0
DEV = /dev/ttyACM0
MCU = TM4C123GH6PM

# === Paths ===
TOOLCHAIN_PATH ?= /home/predator/tools/gcc-arm-none-eabi-10.3-2021.10/bin# Path to ARM GCC Toolchain
LD_PATH ?= ld/TM4C123GH6PM.ld# Path to linker script
CMSIS_PATH ?= CMSIS# Path to CMSIS directory
OBJ := obj/ # Object files directory

# === Toolchain Binaries ===
CC := $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
LD := $(TOOLCHAIN_PATH)/arm-none-eabi-ld
OBJCOPY := $(TOOLCHAIN_PATH)/arm-none-eabi-objcopy
ASM := $(TOOLCHAIN_PATH)/arm-none-eabi-as
OBJDUMP := $(TOOLCHAIN_PATH)/arm-none-eabi-objdump
SIZE := $(TOOLCHAIN_PATH)/arm-none-eabi-size
FLASHER = lm4flash #flashing utility



# === Source Files ===
SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/app/*.c) # Add all C source files in CMSIS directory
SRCS += $(wildcard $(SRC_DIR)/drivers/*.c) # Add all C source files in src and drivers directories
SRCS += $(wildcard $(SRC_DIR)/middleware/*.c) #$(wildcard $(SRC_DIR)/middleware/*.s)# Add all C source files in CMSIS directory
# STARTUP_SRC := $(wildcard $(SRC_DIR)/middleware/*.s)
# STARTUP_OBJ := $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(STARTUP_SRC)) # Convert startup assembly files to object files


# == Object Files ===
# OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) # Convert source files to object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) # Convert source files to object files
# OBJS += $(STARTUP_OBJ) # Add startup object file to the list of object files


# === Includes ===
INCLUDES := -Iinclude 
INCLUDES += -I$(SRC_DIR)/drivers -I$(CMSIS_PATH) -I$(CMSIS_PATH)/m-profile	# Include directories for headers

# === Compiler/Linker Flags ===
CFLAGS = -ggdb -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -Os -MD -std=c99 -Wall 
CFLAGS += -DPART_TM4C123GH6PM -ffunction-sections -fdata-sections
LDFLAGS := -T$(LD_PATH) -nostdlib -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--gc-sections --specs=nosys.specs -lc -lgcc  
ASM_FLAGS := -mcpu=cortex-m4 -mthumb 

# === Targets ===

all: $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	$(MKDIR)          
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@ 

$(STARTUP_OBJ): $(STARTUP_SRC)
	mkdir -p $(dir $@)
	$(ASM) -c $< -o $@ 

# ELF generation
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	$(SIZE) $@

# Convert to binary
$(BUILD_DIR)/$(TARGET).bin:$(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Flash with OpenOCD or lm4flasher (make sure config is correct)
flash:
# 	openocd -f interface/cmsis-dap.cfg -f target/stellaris.cfg -c "program $(BUILD_DIR)/$(TARGET).bin verify reset exit 0x00000000"
	$(FLASHER) -S $(DEV) $(BUILD_DIR)/$(TARGET).bin

# Disassemble
disasm:
	$(OBJDUMP) -D $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).lst

clean:
	$(RM) $(BUILD_DIR)

.PHONY: all clean bin flash disasm