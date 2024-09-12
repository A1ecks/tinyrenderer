SHELL = Powershell.exe
.SHELLFLAGS = -NoProfile -Command

CXX := g++
SRC_DIR := src
BUILD_DIR := build
TARGET := bin/run
SRC_EXT := cpp
SRCS := $(shell gci -r -name -fi *.$(SRC_EXT))
OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.$(SRC_EXT)=.o))
CXXFLAGS := -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17
INC := -I include

# Default rule to build and run executable
.PHONY: all
all: $(TARGET) run

# Link objects to executable
$(TARGET): $(OBJS)
	$(CXX) $^ -o $(TARGET) $(CXXFLAGS)

# Compile source files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $< -save-temps -03

# Run executable
.PHONY: run
run: $(TARGET)
	$(TARGET)

# Remove generated files
.PHONY: clean
clean:
	rm -r $(SRC_DIR)/*.o; rm -r $(TARGET).exe
