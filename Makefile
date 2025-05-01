# Makefile for Programming Assignment

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Output binary name
TARGET = DES

# Source files
SRC = DES.cpp

# Object files (derived from source files)
OBJ = DES.o

# Default target to build the program
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to create the object file (.o)
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Clean up the generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

