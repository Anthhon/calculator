#!/bin/bash

CC=gcc
FLAGS=-Wall -Werror -Wextra -pedantic
LIBS=-lm

SRC_PATH=src
BUILD_PATH=build
EXECUTABLE=calc

all: build

build-linux:
	@echo "[+] Checking build folder existence..."
	mkdir -p $(BUILD_PATH)
	@echo "[+] Building project..."
	$(CC) $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) 
	@echo "[+] Project built successfully!"


install-linux:
	@echo "[+] Checking build folder existence..."
	mkdir -p $(BUILD_PATH)
	@echo "[+] Building project..."
	$(CC) $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) 
	@echo "[+] Project built successfully!"
	@read -p "Do you want to install the binary to /usr/local/bin? (y/n): " answer; \
	if [ "$$answer" != "${answer#[Yy]}" ]; then \
		sudo cp $(BUILD_PATH)/$(EXECUTABLE) /usr/local/bin/; \
		echo "[+] Binary installed to /usr/local/bin/"; \
	else \
		echo "[+] Installation aborted."; \
	fi

build-windows:
	@echo "[+] Building project..."
	i686-w64-mingw32-gcc $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE).exe $(SRC_PATH)/*.c $(LIBS)
	@echo "[+] Project built successfully!"

debug:
	@echo "[+] Checking build folder existence..."
	mkdir -p $(BUILD_PATH)
	@echo "[+] Building project..."
	$(CC) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) -g
	@echo "[+] Project built successfully!"

gprof-build:
	@echo "[+] Checking build folder existence..."
	mkdir -p $(BUILD_PATH)
	@echo "[+] Building project..."
	$(CC) $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) -g -pg
	@echo "[+] Project built successfully!"

run:
	./$(BUILD_PATH)/$(EXECUTABLE)

clean:
	@echo "[!] Removing content from `$(BUILD_PATH)`"
	rm -i $(BUILD_PATH)/*
