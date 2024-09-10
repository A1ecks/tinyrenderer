SHELL = Powershell.exe
.SHELLFLAGS = -NoProfile -Command

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

# Directories
BUILD_DIR = bin
SRC_DIR = src
OBJ_DIR = obj

# Target executable
TARGET = $(BUILD_DIR)/main

# For deleting the target
TARGET_DEL := $(TARGET).exe

# Source files
SRCS := $(shell gci src -r -name -fi '*.cpp')

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJ_DIR)/$(OBJS)
	$(CXX) -o $(TARGET) $(OBJ_DIR)/$(OBJS) $(CXXFLAGS) 

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/$(OBJS): $(SRC_DIR)/$(SRCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	$(TARGET)

# Clean rule to remove generated files
clean:
	rm $(TARGET_DEL); rm $(OBJ_DIR)/$(OBJS)
