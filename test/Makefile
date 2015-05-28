

CC=propeller-elf-gcc
FLASH=propeller-load
PROPELLER_LOAD_CONFIG=$(PROPELLER_GCC_HOME)/propeller-load

CFLAGS=-Os -m32bit-doubles -fno-exceptions -std=c99 -mlmm
BOARD=QUICKSTART

BUILD=../build
INCLUDES=-I../include
OBJ=ringbuffer-test.o

.PHONY: all clean load

all: ringbuffer-test test


clean:
	rm -rf ringbuffer-test *.o

%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

ringbuffer-test: $(OBJ)
	$(CC) $(BUILD)/ringbuffer.o $(OBJ) -o ringbuffer-test

test: ringbuffer-test
	${FLASH} -b ${BOARD} -p ${PROPELLER_GCC_PORT} -I ${PROPELLER_LOAD_CONFIG} -r $<
