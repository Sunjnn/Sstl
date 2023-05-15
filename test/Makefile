CC = g++
ROOT_DIR = $(shell realpath ..)
BUILD_DIR = $(ROOT_DIR)/build
SSTL_DIR = $(ROOT_DIR)/Sstl
CFLAGS = -I $(SSTL_DIR)

test_vector: test_vector.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

test_list: test_list.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

test_deque: test_deque.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

test_stack:test_stack.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

test_queue: test_queue.cpp $(SSTL_DIR)/*
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@
