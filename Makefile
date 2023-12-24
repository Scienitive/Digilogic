NAME=digilogic
CC=clang

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

CFLAGS=-g -Wextra -Wall $(shell pkg-config --cflags raylib)
LDFLAGS=$(shell pkg-config --libs raylib)

SRCS=$(shell find $(SRC_DIR) -name '*.c')
OBJS=$(patsubst $(SRC_DIR)/*.c, $(OBJ_DIR)/*.o, $(SRCS))
BIN=$(BIN_DIR)/$(NAME)

all: $(BIN) run

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@

clean:
	$(RM) -r $(BIN_DIR)/* $(OBJ_DIR)/*

re: clean all

run:
	./$(BIN_DIR)/$(NAME)

.PHONY: clean run re
