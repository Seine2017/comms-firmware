# Board type (uno, promicro, nano):
BOARD = promicro
# Name of microcontroller (atmega328p, atmega32u4):
MCU = atmega32u4
# Microcontroller clock frequency (Hz).
F_CPU = 16000000

# Name of C compiler:
CC = avr-gcc
# Flags passed to C preprocessor:
CPPFLAGS = -Isrc -DF_CPU=$(F_CPU) -DBOARD_$(BOARD)=1
# Flags passed to C compiler:
CFLAGS = -O3 -Wall -Wno-unused-function -mmcu=$(MCU)
# Name of linker:
LD = avr-gcc
# Flags passed to linker:
LDFLAGS = -mmcu=$(MCU) -Wl,-u,vfprintf -lprintf_flt
# Name of objcopy tool:
OBJCOPY = avr-objcopy
# Name of size tool:
SIZE = avr-size

SOURCES = src/main.c src/clock.c src/comms.c src/data_conversion.c src/debug.c src/rc_receiver.c src/rf_transceiver.c src/includes/receiver.c src/includes/spi.c src/includes/transmitter.c
OBJECTS = $(SOURCES:.c=.o)

all: comms-firmware.hex

comms-firmware.hex: comms-firmware.elf
	$(OBJCOPY) -O ihex $< $@
	$(SIZE) $@

comms-firmware.elf: $(OBJECTS)
	$(LD) -lc -lm $(LDFLAGS) -o $@ $^ -lc

*.o: *.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<

clean:
	rm -f *.hex *.elf src/*.o

flash:
	avrdude -p$(MCU) -cc232hm -P/dev/ttyUSB0 -b57600 -U flash:w:comms-firmware.hex:i
