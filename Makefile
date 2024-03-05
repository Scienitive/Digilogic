NAME=digilogic
CC=clang++

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

CFLAGS=-g -Wextra -Wall -std=c++11 $(shell pkg-config --cflags raylib) -I/usr/local/include
LDFLAGS=$(shell pkg-config --libs raylib) -L/usr/local/lib -lyogacore

SRCS=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(patsubst $(SRC_DIR)/*.cpp, $(OBJ_DIR)/*.o, $(SRCS))
BIN=$(BIN_DIR)/$(NAME)

all: $(BIN) run

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@

clean:
	$(RM) -r $(BIN_DIR)/* $(OBJ_DIR)/*

re: clean all

run:
	./$(BIN_DIR)/$(NAME)

.PHONY: clean run re
