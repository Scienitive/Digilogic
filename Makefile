NAME=digilogic
CC=clang
CFLAGS=-g -Wextra -Wall

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/*.c, $(OBJ_DIR)/*.o, $(SRCS))
BIN=$(BIN_DIR)/$(NAME)

INC=`pkg-config --cflags raylib`
LIBS=`pkg-config --libs raylib`


all: $(BIN) run

$(BIN): $(OBJS)
	$(CC) $(INC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INC) $(CFLAGS) -c $< $(LIBS) -o $@

clean:
	$(RM) -r $(BIN_DIR)/* $(OBJ_DIR)/*

run:
	./$(BIN_DIR)/$(NAME)

.PHONY: clean run
