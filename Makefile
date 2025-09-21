# Makefile for Vending Machine Project

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = vending_machine
SOURCES = main.c product.c inventory.c transaction.c display.c input.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = vending_machine.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Build completed successfully!"
	@echo "Run with: ./$(TARGET)"

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean completed!"

# Rebuild everything
rebuild: clean all

# Install dependencies (if any were needed)
install:
	@echo "No external dependencies required for this project."

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the vending machine program (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and rebuild"
	@echo "  run      - Build and run the program"
	@echo "  debug    - Build with debug symbols"
	@echo "  help     - Show this help message"

.PHONY: all clean rebuild install run debug help