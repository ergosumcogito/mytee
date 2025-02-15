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
    RM = rm -rf $(BUILD_DIR) $(TARGET) test_unit test_integration
endif

# Main sources
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = mytee

# Exclude main.o from test builds
MAIN_OBJS = $(filter-out $(BUILD_DIR)/main.o, $(OBJS))

all: $(TARGET)

$(BUILD_DIR):
	$(MKDIR)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Unit test binary
UNIT_TEST_SRC = $(TEST_DIR)/unit-tests.c
UNIT_TEST_OBJ = $(BUILD_DIR)/unit-tests.test.o
UNIT_TEST_TARGET = test_unit

test-unit: $(UNIT_TEST_TARGET)
	./$(UNIT_TEST_TARGET)

$(UNIT_TEST_TARGET): $(UNIT_TEST_OBJ) $(MAIN_OBJS)
	$(CC) $(UNIT_TEST_OBJ) $(MAIN_OBJS) -o $(UNIT_TEST_TARGET)

$(BUILD_DIR)/unit-tests.test.o: $(UNIT_TEST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Integration test binary
INTEGRATION_TEST_SRC = $(TEST_DIR)/integration-tests.c
INTEGRATION_TEST_OBJ = $(BUILD_DIR)/integration-tests.test.o
INTEGRATION_TEST_TARGET = test_integration

test-integration: $(TARGET) $(INTEGRATION_TEST_TARGET)
	./$(INTEGRATION_TEST_TARGET)

$(INTEGRATION_TEST_TARGET): $(INTEGRATION_TEST_OBJ) $(MAIN_OBJS)
	$(CC) $(INTEGRATION_TEST_OBJ) $(MAIN_OBJS) -o $(INTEGRATION_TEST_TARGET)

$(BUILD_DIR)/integration-tests.test.o: $(INTEGRATION_TEST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Run all tests
test: test-unit test-integration

TEST_FILES = empty_test.txt test1.txt test2.txt test_append.txt test_output.txt

clean:
	$(RM) $(TEST_FILES)
	@echo "Test files cleaned: $(TEST_FILES)"
