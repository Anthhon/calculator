#!/bin/bash

CC=gcc
FLAGS=-Wall -Werror -Wextra -pedantic
LIBS=-lm

SRC_PATH=src
BUILD_PATH=build
EXECUTABLE=calc

all: build

build:
	@echo "[+] Building project..."
	$(CC) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c
	@echo "[+] Project built successfully!"

debug:
	@echo "[+] Building project..."
	$(CC) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c -g
	@echo "[+] Project built successfully!"

run:
	./$(BUILD_PATH)/$(EXECUTABLE)

clean:
	@echo "[!] Removing content from `$(BUILD_PATH)`"
	rm -i $(BUILD_PATH)/*
