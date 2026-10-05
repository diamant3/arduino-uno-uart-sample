PROG_NAME = usart
SRC_DIR = src
OUT_DIR = out

all: $(PROG_NAME)

$(OUT_DIR):
	mkdir -pv $(OUT_DIR)

$(PROG_NAME): $(OUT_DIR)
	avr-gcc -mmcu=atmega328p -Wall -Os -o $(OUT_DIR)/$(PROG_NAME).elf $(SRC_DIR)/$(PROG_NAME).c
	avr-objcopy -j .text -j .data -O ihex $(OUT_DIR)/$(PROG_NAME).elf $(OUT_DIR)/$(PROG_NAME).hex

upload: $(PROG_NAME)
	avrdude -F -V -c arduino -p m328p -P /dev/ttyUSB0 -U flash:w:$(OUT_DIR)/$(PROG_NAME).hex

clean:
	rm -rf $(OUT_DIR)
