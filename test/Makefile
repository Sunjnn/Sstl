CC = g++
ROOT_DIR = $(shell realpath ..)
BUILD_DIR = $(ROOT_DIR)/build
CFLAGS = -I $(ROOT_DIR)/Sstl

test_vector: test_vector.cpp ../Sstl/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@
