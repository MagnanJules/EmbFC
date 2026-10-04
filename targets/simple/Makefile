CC      := arm-none-eabi-gcc
CFLAGS  := -mcpu=cortex-m4 -mthumb -O1 -g -Wall -Wextra -ffreestanding
LDFLAGS := -nostdlib -T link.ld

target.elf: target.c link.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ target.c

clean:
	rm -f target.elf

.PHONY: clean
