# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -I./include

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
INCLUDE_DIR = include

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM = if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR) & if exist $(TARGET).exe del /f /q $(TARGET).exe
else
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf $(BUILD_DIR) $(TARGET) test_tee
endif

# Main sources
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = mytee

# Exclude main.o from test build
MAIN_OBJS = $(filter-out $(BUILD_DIR)/main.o, $(OBJS))

all: $(TARGET)

$(BUILD_DIR):
	$(MKDIR)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build test binary
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.test.o, $(TEST_SRCS))
TEST_TARGET = test_tee

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(MAIN_OBJS)
	$(CC) $(TEST_OBJS) $(MAIN_OBJS) -o $(TEST_TARGET)

$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	$(RM)
