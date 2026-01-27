# =============================
# Makefile cho STM32F407 Linux
# =============================

# Toolchain
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

DEFS = -DSTM32F407xx -DUSE_HAL_DRIVER
# MCU flags
MCU     = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Include paths
INC = -I./Core/Inc \
      -IDrivers/CMSIS/Include \
      -IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
      -IDrivers/STM32F4xx_HAL_Driver/Inc

# Source files
SRC = ./main.c \
      Core/Src/system_stm32f4xx.c \
      Core/Src/init.c \
	  Core/Src/gpio.c \
	  Core/Src/rcc.c \
	  Core/Src/exti.c \
	  Core/Src/it.c \
	  Core/Src/spi_driver.c
	  
STARTUP = Core/Startup/startup_stm32f407vgtx.s

# Object files
OBJ = $(SRC:.c=.o) \
      $(STARTUP:.s=.o)

# Output
TARGET = main.elf
HEX    = main.hex
BIN    = main.bin

# Compiler flags
CFLAGS = $(MCU) $(DEFS) -O0 -g3 -Wall -Wextra $(INC)
LDFLAGS = $(MCU) -TSTM32F407VGTX_FLASH.ld -nostartfiles -Wl,-Map=$(TARGET:.elf=.map)

# -----------------------------
# Rules
# -----------------------------

all: $(TARGET) $(HEX) $(BIN) size

# Compile C sources
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile startup assembly
%.o: %.s
	$(CC) $(MCU) -c -o $@ $<

# Link
$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Generate HEX and BIN
%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

# Show size
size: $(TARGET)
	$(SIZE) $<

# Clean
clean:
	rm -f $(OBJ) $(TARGET) $(HEX) $(BIN) *.map

.PHONY: all clean size
# ------------------------------------------------
# PHẦN THÊM VÀO: Flash & Debug (OpenOCD + GDB)
# ------------------------------------------------

# Cấu hình mạch nạp (Mặc định là ST-Link V2 cho STM32F4 Discovery/Nucleo)
# Nếu dùng mạch nạp khác (J-Link), sửa dòng này thành interface/jlink.cfg
# OCD_INTERFACE = interface/stlink.cfg
# OCD_TARGET    = target/stm32f4x.cfg
OPENOCD_WIN_PATH = /mnt/c/OpenOCD-20251211-0.12.0/bin/openocd.exe
OPENOCD_SCRIPTS  = /mnt/c/OpenOCD-20251211-0.12.0/share/openocd/scripts
# 1. Target nạp code (Flash)
# Lệnh: make flash
# flash: $(TARGET)
# 	@echo "Dang nap code xuong chip..."
# 	openocd -f $(OCD_INTERFACE) -f $(OCD_TARGET) -c "program $(TARGET) verify reset exit"

flash: $(TARGET)
	@echo "Dang nap code..." 
	$(OPENOCD_WIN_PATH) -s $(OPENOCD_SCRIPTS) \
	-f interface/stlink-v2.cfg \
	-f target/stm32f4x.cfg \
	-c "program $(TARGET) verify reset exit"
	
# 2. Target Debug (GDB TUI)
# Lệnh: make debug
# Lưu ý: Cần mở một terminal khác chạy lệnh: openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
# 2. Target Debug (GDB TUI)
debug: $(TARGET)
	@echo "Dang mo GDB..."
	gdb-multiarch $(TARGET) \
	-ex "target remote localhost:3333" \
	-ex "monitor reset halt" \
	-ex "tui enable" \
	-ex "layout src"

# 3. Target Debug Makefile (In giá trị biến)
# Lệnh: make print-CFLAGS (để xem cờ biên dịch) hoặc make print-SRC
print-%:
	@echo $* = $($*)