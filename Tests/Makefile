CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Werror -pedantic
CPPFLAGS := -I../Peripheral/inc -I../Driver/Core/Inc $(CPPFLAGS)
BUILD_DIR := build
TARGET := $(BUILD_DIR)/test_lis3dsh

.PHONY: all test clean

all: test

test: $(TARGET)
	./$(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): peripheral/test_lis3dsh.c ../Peripheral/src/lis3dsh.c ../Peripheral/inc/lis3dsh.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) peripheral/test_lis3dsh.c ../Peripheral/src/lis3dsh.c -o $@

clean:
	rm -rf $(BUILD_DIR)
