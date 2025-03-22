# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Source files
SRC = main.cpp hashTable.cpp linkedList.cpp

# Object files (replace .cpp with .o)
OBJ = $(SRC:.cpp=.o)

# Executable name
TARGET = program

# Default target
all: $(TARGET)

# Link object files to create final executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program (compile first if needed)
run: all
	./$(TARGET)

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)
