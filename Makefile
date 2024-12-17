CC = gcc
CFLAGS = -Wall -std=c99

# Define the executable, name of .exe
TARGET = mytee

# Define the source files
SRCS = main.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the target rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Clean the build
clean:
	rm -f $(OBJS) $(TARGET)
