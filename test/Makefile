CC = g++
ROOT_DIR = $(shell realpath ..)
BUILD_DIR = $(ROOT_DIR)/build
SSTL_DIR = $(ROOT_DIR)/Sstl
CFLAGS = -I $(SSTL_DIR)

.PHONY: default
default:
	@echo "file <test/Makefile> match no pattern"

.PHONY: test_%
test_%: test_%.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

.PHONY: test_debug_%
test_debug_%: test_%.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) -g $< -o $(BUILD_DIR)/$@
