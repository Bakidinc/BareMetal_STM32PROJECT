BINARY         = firmware
SRC_DIR        = src
INC_DIR        = inc
OPENCM3_DIR    = ../libopencm3
SHARED_SRC_DIR = ../shared/src
SHARED_INC_DIR = ../shared/inc

LIBNAME     = opencm3_stm32f4
DEFS        += -DSTM32F4
FP_FLAGS    ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS  = -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

LDSCRIPT    = linkerscript.ld
LDLIBS      += -l$(LIBNAME)
LDFLAGS     += -L$(OPENCM3_DIR)/lib

DEFS        += -I$(OPENCM3_DIR)/include
DEFS        += -I$(INC_DIR)
DEFS        += -I$(SHARED_INC_DIR)

PREFIX      ?= arm-none-eabi-
CC          := $(PREFIX)gcc
LD          := $(PREFIX)gcc
OBJCOPY     := $(PREFIX)objcopy
OBJDUMP     := $(PREFIX)objdump
OPT			:= -O0
DEBUG       := -ggdb3
CSTD        ?= -std=c99


OBJS        += $(SRC_DIR)/firmware.o
#OBJS      	+= $(SRC_DIR)/core/system.o  
OBJS        += $(SRC_DIR)/timer.o
OBJS        += $(SHARED_SRC_DIR)/core/system.o
OBJS        += $(SHARED_SRC_DIR)/core/uart.o

TGT_CFLAGS  += $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS  += $(ARCH_FLAGS)
TGT_CFLAGS  += -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS  += -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS  += -fno-common -ffunction-sections -fdata-sections

TGT_CPPFLAGS += -MD -Wall -Wundef $(DEFS)

TGT_LDFLAGS += --static -nostartfiles
TGT_LDFLAGS += -T$(LDSCRIPT)
TGT_LDFLAGS += $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS += -Wl,-Map=$(BINARY).map -Wl,--cref -Wl,--gc-sections

LDLIBS      += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

all: elf bin

elf: $(BINARY).elf
bin: $(BINARY).bin

$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(MAKE) -C $(OPENCM3_DIR)

%.bin: %.elf
	@echo "  OBJCOPY $@"
	@$(OBJCOPY) -Obinary $< $@

%.elf: $(OBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a Makefile
	@echo "  LD      $@"
	@$(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

%.o: %.c
	@echo "  CC      $<"
	@$(CC) $(TGT_CFLAGS) $(TGT_CPPFLAGS) -o $@ -c $<

clean:
	@echo "  CLEAN"
	@rm -f *.elf *.bin *.hex *.list *.map *.d *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d

.PHONY: clean elf bin
-include $(OBJS:.o=.d)