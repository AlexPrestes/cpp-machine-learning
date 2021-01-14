CPP_MACHINE_LEARNING_ROOT := $(PWD)/..
CC=g++
SRC := $(CPP_MACHINE_LEARNING_ROOT)/kNN/src
CFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2 -DEUCLID
INCLUDE_DIR := $(CPP_MACHINE_LEARNING_ROOT)/kNN/include/

all := main

main : $(SRC)/knn.cpp
	$(CC) $(CFLAGS) $(SRC)/knn.cpp -o main -L$(CPP_MACHINE_LEARNING_ROOT)/lib -I$(INCLUDE_DIR) \
	-I$(CPP_MACHINE_LEARNING_ROOT)/include -ldata

clean :
	rm main