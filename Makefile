#!/bin/bash

CC=gcc
FLAGS=-Wall -Werror -Wextra -pedantic
LIBS=-lm

SRC_PATH=src
BUILD_PATH=build
EXECUTABLE=calc

all: build

build-linux:
	@echo "[+] Building project..."
	$(CC) $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) 
	@echo "[+] Project built successfully!"


build-windows:
	@echo "[+] Building project..."
	i686-w64-mingw32-gcc $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE).exe $(SRC_PATH)/*.c $(LIBS)
	@echo "[+] Project built successfully!"

debug:
	@echo "[+] Building project..."
	$(CC) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) -g
	@echo "[+] Project built successfully!"

gprof-build:
	@echo "[+] Building project..."
	$(CC) $(FLAGS) -o $(BUILD_PATH)/$(EXECUTABLE) $(SRC_PATH)/*.c $(LIBS) -g -pg
	@echo "[+] Project built successfully!"

run:
	./$(BUILD_PATH)/$(EXECUTABLE)

clean:
	@echo "[!] Removing content from `$(BUILD_PATH)`"
	rm -i $(BUILD_PATH)/*
