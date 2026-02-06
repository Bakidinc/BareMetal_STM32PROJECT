BINARY = bootloader
SRC_DIR = src
INC_DIR = inc
OPENCM3_DIR = ../libopencm3

LIBNAME     = opencm3_stm32f4
DEFS        += -DSTM32F4

# --- DÜZELTME 1: FPU AYARI GÜNCELLENDİ (KRİTİK) ---
# Libopencm3 STM32F4 için varsayılan olarak "hard float" ile derlenir.
# "soft" kullanmak ABI uyuşmazlığına ve kodun şişmesine (ROM taşması) sebep olur.
# Aşağıdaki satır bu uyuşmazlığı çözer:
FP_FLAGS    ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS  = -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

LDSCRIPT    = linkerscript.ld

# Libopencm3 kütüphanesini ekle
LDLIBS      += -l$(LIBNAME)
LDFLAGS     += -L$(OPENCM3_DIR)/lib

DEFS        += -I$(OPENCM3_DIR)/include
DEFS        += -I$(INC_DIR)

PREFIX      ?= arm-none-eabi-
CC          := $(PREFIX)gcc
LD          := $(PREFIX)gcc
OBJCOPY     := $(PREFIX)objcopy
OBJDUMP     := $(PREFIX)objdump

# --- OPTİMİZASYON ---
# -Os: Boyut optimizasyonu (Bootloader için en iyisi)
OPT         := -Os
DEBUG       := -ggdb3
CSTD        ?= -std=c99

# Kaynak dosyanın yolu
OBJS        += $(SRC_DIR)/bootloader.o

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

# --- DÜZELTME 2: SPECS AYARLARI ---
# Nano specs ve nosys specs boyutu küçültmek için gereklidir.
TGT_LDFLAGS += --specs=nano.specs --specs=nosys.specs

# --- KÜTÜPHANELER ---
# Standart C kütüphanesini (libc) bootloader'da kullanmıyorsan çıkarabilirsin.
# Ancak matematiksel işlemler vs. varsa -lc gerekebilir.
# Şimdilik senin ayarını koruyorum (-lgcc yeterli görünüyor):
LDLIBS      += -Wl,--start-group -lgcc -Wl,--end-group

all: elf bin

elf: $(BINARY).elf
bin: $(BINARY).bin

# Kütüphaneyi derle
$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(MAKE) -C $(OPENCM3_DIR)

# ELF Oluşturma
$(BINARY).elf: $(OBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a Makefile
	@echo "  LD      $@"
	@$(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

# BIN Oluşturma
$(BINARY).bin: $(BINARY).elf
	@echo "  OBJCOPY $@"
	@$(OBJCOPY) -Obinary $< $@
	python pad-bootloader.py

# Obje dosyası oluşturma
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "  CC      $<"
	@$(CC) $(TGT_CFLAGS) $(TGT_CPPFLAGS) -o $@ -c $<

clean:
	@echo "  CLEAN"
	@rm -f *.elf *.bin *.hex *.list *.map *.d *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d

.PHONY: clean elf bin
-include $(OBJS:.o=.d)