.POSIX:

TARGET := main
BUILD_DIR := build
INC_DIR := include
SRC_DIR := src

MCU_VARIANT := STM32F767xx
CPU := cortex-m7
F_CPU := 216000000L

CUBE_DIR := vendor
VERBOSE := 0

###############################################################################

CROSS_COMPILE := arm-none-eabi
AS := $(CROSS_COMPILE)-as
AR := $(CROSS_COMPILE)-ar
CC := $(CROSS_COMPILE)-gcc
LD := $(CROSS_COMPILE)-ld
OBJCOPY := $(CROSS_COMPILE)-objcopy
OBJDUMP := $(CROSS_COMPILE)-objdump
SIZE := $(CROSS_COMPILE)-size
GDB := $(CROSS_COMPILE)-gdb

###############################################################################

MCU_VARIANT_LC := $(shell echo $(MCU_VARIANT) | tr "[:upper:]" "[:lower:]")
MCU_VARIANT_UC := $(subst x,X,$(MCU_VARIANT))
MCU_FAMILY_LC := $(shell v=$(MCU_VARIANT_LC); echo $${v%????}xx)
MCU_FAMILY_MC := $(shell v=$(MCU_VARIANT_UC); echo $${v%????}xx)

HAL_DIR := $(CUBE_DIR)/Drivers/$(MCU_FAMILY_MC)_HAL_Driver
CMSIS_DIR := $(CUBE_DIR)/Drivers/CMSIS
DEVICE_DIR := $(CMSIS_DIR)/Device/ST/$(MCU_FAMILY_MC)

HAL_MODULES = $(shell grep -o '^#define HAL_.*_MODULE_ENABLED' \
	$(INC_DIR)/$(MCU_FAMILY_LC)_hal_conf.h | \
	cut -d'_' -f2 | tr '[:upper:]' '[:lower:]')
HAL_SRCS := $(MCU_FAMILY_LC)_hal.c $(HAL_MODULES:%=$(MCU_FAMILY_LC)_hal_%.c)
HAL_EX_SRCS := $(foreach module,$(HAL_MODULES), \
	$(wildcard $(HAL_DIR)/Src/*$(module)_ex.c))
HAL_SRCS += $(HAL_EX_SRCS:$(HAL_DIR)/Src/%=%)

OPENOCD_TARGET := $(shell v=$(MCU_VARIANT_LC); echo "target/$${v%????}x.cfg")

# Prettify output
ifeq ($(VERBOSE), 0)
	Q := @
	P := > /dev/null
	OPENOCD_VERBOSITY=1
else
	OPENOCD_VERBOSITY=2
endif

###############################################################################

# Source search paths
VPATH := $(SRC_DIR) $(SRC_DIR)/sensors
VPATH += $(HAL_DIR)/Src
VPATH += $(DEVICE_DIR)/Source
VPATH += $(DEVICE_DIR)/Source/Templates
VPATH += $(DEVICE_DIR)/Source/Templates/gcc

S_SRCS := startup_$(MCU_VARIANT_LC).s
S_OBJS += $(S_SRCS:%.s=$(BUILD_DIR)/%.o)

C_SRCS := $(subst $(SRC_DIR)/,,$(wildcard $(SRC_DIR)/*.c))
C_SRCS += $(subst $(SRC_DIR)/sensors/,,$(wildcard $(SRC_DIR)/sensors/*.c))
C_SRCS += $(HAL_SRCS)
C_SRCS += system_$(MCU_FAMILY_LC).c
C_OBJS := $(C_SRCS:%.c=$(BUILD_DIR)/%.o)

DEFS := -D$(MCU_VARIANT) -DF_CPU=$(F_CPU)

INCS := -I$(INC_DIR)
INCS += -I$(CMSIS_DIR)/Include
INCS += -I$(DEVICE_DIR)/Include
INCS += -I$(HAL_DIR)/Inc

COMMON_FLAGS := -mthumb -mcpu=$(CPU) -mfloat-abi=hard -mfpu=fpv5-d16
LDFILE := linker-script.ld

ASFLAGS := $(COMMON_FLAGS)
CFLAGS := $(COMMON_FLAGS) -Wall -g -Os
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -nostdlib $(INCS) $(DEFS)
LDFLAGS := $(COMMON_FLAGS) -Os -L$(CMSIS_DIR)/Lib
LDFLAGS += --specs=nano.specs --specs=nosys.specs
LDFLAGS += -Wl,--gc-sections,--relax,--no-warn-rwx-segments
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,-T$(LDFILE)
LDFLAGS += -Wl,--undefined,_printf_float

###############################################################################

all: $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR):
	@echo "[MKDIR]   $@"
	$Qmkdir -p $@

$(S_OBJS): $(BUILD_DIR)/%.o: %.s |  $(BUILD_DIR)
	@echo "[AS]      $(notdir $<)"
	$Q$(COMPILE.s) -o $@ $<

$(C_OBJS): $(BUILD_DIR)/%.o: %.c $(INC_DIR)/main.h | $(BUILD_DIR)
	@echo "[CC]      $(notdir $<)"
	$Q$(COMPILE.c) -o $@ $<

$(BUILD_DIR)/$(TARGET).elf: $(C_OBJS) $(S_OBJS)
	@echo "[LD]      $@"
	$Q$(LINK.o) $^ $(LDLIBS) -o $@
	@echo "[OBJDUMP] $(BUILD_DIR)/$(TARGET).lst"
	$Q$(OBJDUMP) -St $@ >$(BUILD_DIR)/$(TARGET).lst
	@echo "[SIZE]    $@"
	$Q$(SIZE) $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo "[OBJCOPY] $@"
	$Q$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -d$(OPENOCD_VERBOSITY) -f interface/stlink.cfg -f \
		$(OPENOCD_TARGET) -c "program $< verify reset exit"

clean:
	@echo "[RM]      $(BUILD_DIR)"; $(RM) -r $(BUILD_DIR)

.PHONY: all program debug clean
