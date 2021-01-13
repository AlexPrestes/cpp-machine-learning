CPP_MACHINE_LEARNING_ROOT := .
CC=g++
INCLUDE_DIR := $(CPP_MACHINE_LEARNING_ROOT)/include
SRC := $(CPP_MACHINE_LEARNING_ROOT)/src
CFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
LIB_DATA := libdata.so

all := $(LIB_DATA)

$(LIB_DATA) : libdir objdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -o $(CPP_MACHINE_LEARNING_ROOT)/lib/$(LIB_DATA) obj/*.o
	rm -r $(CPP_MACHINE_LEARNING_ROOT)/obj

libdir :
	mkdir -p $(CPP_MACHINE_LEARNING_ROOT)/lib

objdir :
	mkdir -p $(CPP_MACHINE_LEARNING_ROOT)/obj

obj/data_handler.o : $(SRC)/data_handler.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SRC)/data_handler.cpp

obj/data.o : $(SRC)/data.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SRC)/data.cpp

clean :
	rm -r $(CPP_MACHINE_LEARNING_ROOT)/lib
	rm -r $(CPP_MACHINE_LEARNING_ROOT)/obj

