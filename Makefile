CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -I./include

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Detect operating system and define commands accordingly
ifeq ($(OS),Windows_NT)
    # Windows commands: use CMD syntax
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM = if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR) & if exist $(TARGET).exe del /f /q $(TARGET).exe
else
    # Linux/macOS commands
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf $(BUILD_DIR) $(TARGET)
endif

# Define the source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = mytee

all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	$(MKDIR)

# Link object files to create executable
$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files to object files in build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean target: remove build directory and executable
clean:
	$(RM)