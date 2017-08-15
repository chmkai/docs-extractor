# Makefile

# Globals:

EXEC = docs-ex

CC = g++-7
CFLAGS = -Wall
TARGET = bin/$(EXEC)

# Source files
SRC = docs_ex.cpp

# Main target:

all:
	cd bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
