CC = g++
ROOT_DIR = $(shell pwd)
BUILD_DIR = $(ROOT_DIR)/build
export CC ROOT_DIR BUILD_DIR

.PHONY: default
default:
	@echo "file <test/Makefile> match no pattern"
	@echo "make test_[structure]"

.PHONY: test_%
test_%: test/test_%.cpp Sstl/*
	make -e -C test $@

test_debug_%: test/test_%.cpp Sstl/*
	make -e -C test $@

.PHONY: test_clean
test_clean:
	rm build/test_*
