MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200
PORT = /dev/ttyUSB0

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
TARGET = usart

SRC_DIR = src
OUT_DIR = out

all: $(OUT_DIR)/$(TARGET).hex

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/$(TARGET).elf: $(SRC_DIR)/$(TARGET).c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(OUT_DIR)/$(TARGET).hex: $(OUT_DIR)/$(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	avr-size --mcu=$(MCU) $<

upload: $(OUT_DIR)/$(TARGET).hex
	avrdude -F -V -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

clean:
	rm -rf $(OUT_DIR)

.PHONY: all upload clean