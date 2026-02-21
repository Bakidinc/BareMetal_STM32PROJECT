BINARY         = firmware
SRC_DIR        = src
INC_DIR        = inc
OPENCM3_DIR    = ../libopencm3
SHARED_SRC_DIR = ../shared/src
SHARED_INC_DIR = ../shared/inc

# Derleme araçları
PREFIX         ?= arm-none-eabi-
CC             := $(PREFIX)gcc
LD             := $(PREFIX)gcc
OBJCOPY        := $(PREFIX)objcopy
OBJDUMP        := $(PREFIX)objdump

# Flag Tanımlamaları
LIBNAME     = opencm3_stm32f4
DEFS        += -DSTM32F4
FP_FLAGS    ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS  = -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

LDSCRIPT    = linkerscript.ld
OPT         := -O0
DEBUG       := -ggdb3
CSTD        ?= -std=c99

# Include Yolları
DEFS        += -I$(OPENCM3_DIR)/include
DEFS        += -I$(INC_DIR)
DEFS        += -I$(SHARED_INC_DIR)

# Kaynak Dosyalar
SOURCES += $(SRC_DIR)/firmware.c
SOURCES += $(SRC_DIR)/timer.c
SOURCES += $(SHARED_SRC_DIR)/core/system.c
SOURCES += $(SHARED_SRC_DIR)/core/uart.c
SOURCES += $(SHARED_SRC_DIR)/core/ring-buffer.c

# Nesne Dosyaları (Build klasörüne yönlendirme)
# Bu yapı, dış klasördeki (../shared) dosyaların .o hallerini yerelde toplar
OBJS = $(SOURCES:.c=.o)

# Derleyici Flagları
TGT_CFLAGS  += $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS  += $(ARCH_FLAGS)
TGT_CFLAGS  += -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS  += -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS  += -fno-common -ffunction-sections -fdata-sections

TGT_CPPFLAGS += -MD -Wall -Wundef $(DEFS)

# Linker Flagları
TGT_LDFLAGS += --static -nostartfiles
TGT_LDFLAGS += -T$(LDSCRIPT)
TGT_LDFLAGS += $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS += -L$(OPENCM3_DIR)/lib
TGT_LDFLAGS += -Wl,-Map=$(BINARY).map -Wl,--cref -Wl,--gc-sections
LDLIBS      += -l$(LIBNAME) -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

# Kurallar
all: elf bin

elf: $(BINARY).elf
bin: $(BINARY).bin

$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	@echo "Kütüphane kontrol ediliyor..."
	$(MAKE) -C $(OPENCM3_DIR)

$(BINARY).bin: $(BINARY).elf
	@echo "  OBJCOPY $@"
	@$(OBJCOPY) -Obinary $< $@

$(BINARY).elf: $(OBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
	@echo "  LD      $@"
	@$(LD) $(TGT_LDFLAGS) $(OBJS) $(LDLIBS) -o $@

# C Dosyalarının Derlenmesi
%.o: %.c
	@echo "  CC      $<"
	@$(CC) $(TGT_CFLAGS) $(TGT_CPPFLAGS) -o $@ -c $<

clean:
	@echo "  CLEAN"
	@rm -f $(BINARY).elf $(BINARY).bin $(BINARY).map
	@rm -f $(SRC_DIR)/*.o $(SRC_DIR)/*.d
	@rm -f $(SHARED_SRC_DIR)/core/*.o $(SHARED_SRC_DIR)/core/*.d

.PHONY: clean elf bin

# Otomatik bağımlılık yönetimi
-include $(OBJS:.o=.d)