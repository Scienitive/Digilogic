NAME=digilogic
TEST_NAME=test
CC=clang++

SRC_DIR=src
TEST_DIR=tests
OBJ_DIR=obj
BIN_DIR=bin

CFLAGS=-g -Wextra -Wall -std=c++11 $(shell pkg-config --cflags raylib) -I/usr/local/include $(TEST_CFLAGS)
TEST_CFLAGS= -I/opt/homebrew/Cellar/doctest/2.4.11/include/doctest
DEBUG_CFLAGS= -ftime-trace
LDFLAGS=$(shell pkg-config --libs raylib) -L/usr/local/lib -lyogacore $(TEST_LDFLAGS)
TEST_LDFLAGS= -L/opt/homebrew/Cellar/doctest/2.4.11/lib

SRCS=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BIN=$(BIN_DIR)/$(NAME)

TEST_SRCS=$(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJS=$(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_BIN=$(BIN_DIR)/$(TEST_NAME)

all: $(BIN) $(TEST_BIN) compile_commands run

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN) run_test

$(TEST_BIN): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: re

clean:
	$(RM) -r $(BIN_DIR)/* $(OBJ_DIR)/*

re: clean all

run:
	./$(BIN_DIR)/$(NAME)

run_test:
	./$(BIN_DIR)/$(TEST_NAME)

compile_commands:
	compiledb -n make

.PHONY: clean run re debug test runt_test compile_commands
