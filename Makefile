CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -Iinclude -pthread
EXECUTABLE=bin/main

SRC_DIR=src
BUILD_DIR=build
BIN_DIR=bin

# Lista de archivos fuente
SRCS=$(wildcard $(SRC_DIR)/*.cc)

# Objetos correspondientes a los archivos fuente
OBJS=$(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar cada archivo fuente en un archivo de objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(EXECUTABLE)
	@echo "Cleaned up"

.PHONY: all clean