OBJECTS=main.o
MAP=main.map
MAKEFILE=Makefile

GCC_DIR=/Users/nathanpage/ti/msp430-gcc/bin
SUPPORT_FILE_DIRECTORY=/Users/nathanpage/ti/msp430-gcc/include

DEVICE  = msp430fr5739
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb

CFLAGS = -I=$(SUPPORT_FILE_DIRECTORY) -L=$(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g main.c

all:
	msp430-elf-gcc -I $(SUPPORT_FILE_DIRECTORY) -L $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g src/main.c -o main.o

clean:
	$(RM) $(OBJECTS)
	$(RM) *.out

debug: all
	$(GDB) $(DEVICE).out