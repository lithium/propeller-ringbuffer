CC=propeller-elf-gcc
AR=propeller-elf-ar
CFLAGS=-Os -m32bit-doubles -mfcache -fno-exceptions -std=c99 -mlmm -ffunction-sections -fdata-sections -Wl,--gc-sections -Dprintf=__simple_printf

INCLUDES=-Iinclude
SRC=src
BUILD=build
TEST=test
SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SOURCES))

OUT=$(BUILD)/ringbuffer.a

.PHONY: test

all: $(BUILD) $(OUT)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o : $(SRC)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJECTS)
	$(AR) rcs $(OUT) $(OBJECTS) 

clean:
	rm -rf $(OBJECTS) $(BUILD) $(OUT)

test:
	$(MAKE) -C $(TEST)
