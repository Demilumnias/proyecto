TARGET = app
CROSS  = riscv64-unknown-elf
CC     = $(CROSS)-gcc
OBJCOPY= $(CROSS)-objcopy
CFLAGS = -Os -Wall -Wextra -ffreestanding -nostdlib -fno-builtin \
         -march=rv32imc -mabi=ilp32
LDFLAGS= -nostdlib -T linker.ld

SRCS = startup.S main.c
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.S=.o)

all: $(TARGET).elf $(TARGET).bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin app_ram.bin
