CMSIS = /home/vic/lib/STM32CubeF1/Drivers/CMSIS

STARTUP = $(CMSIS)/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s
SYSTEM  = $(CMSIS)/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

# list of source files
SOURCES  = main.o os.o

# name for output binary files
PROJECT ?= led

# compiler, objcopy (should be in PATH)
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash

# specify compiler flags
CPPFLAGS := -I$(CMSIS)/Device/ST/STM32F1xx/Include
CPPFLAGS += -I$(CMSIS)/Include
CPPFLAGS += -DSTM32F103xB

CFLAGS := -mcpu=cortex-m3 -g -std=c17 -Wall -Wextra -Wpedantic
CFLAGS += -Os
CFLAGS := -mcpu=cortex-m3
CFLAGS += -g -std=c17 -Wall -Wextra -Wpedantic
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Os

LDSCRIPT := STM32F103XB_FLASH.ld
LDFLAGS := -Wl,-T,$(LDSCRIPT)
LDFLAGS += -Wl,--gc-sections -Wl,--no-warn-rwx-segments


OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf

# compile
$(PROJECT).elf: startup_stm32f103xb.o system_stm32f1xx.o $(SOURCES)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^
	$(OBJCOPY) -O binary $@ $(PROJECT).bin

startup_stm32f103xb.o: $(STARTUP)
	$(AS) -o $@ $<

system_stm32f1xx.o: $(SYSTEM)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# flash
burn:
	sudo $(ST_FLASH) --connect-under-reset write $(PROJECT).bin 0x8000000

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin
