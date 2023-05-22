CC = g++
ROOT_DIR = $(shell pwd)
BUILD_DIR = $(ROOT_DIR)/build
export CC ROOT_DIR BUILD_DIR

test_vector: test/test_vector.cpp Sstl/*
	make -e -C test test_vector

test_list: test/test_list.cpp Sstl/*
	make -e -C test test_list

test_deque: test/test_deque.cpp Sstl/*
	make -e -C test test_deque

test_stack: test/test_stack.cpp Sstl/*
	make -e -C test test_stack

test_queue: test/test_queue.cpp Sstl/*
	make -e -C test test_queue

test_heap: test/test_heap.cpp Sstl/*
	make -e -C test test_heap

test_priority_queue: test/test_priority_queue.cpp Sstl/*
	make -e -C test test_priority_queue
