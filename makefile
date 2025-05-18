CXX := g++

CXX_FLAGS 	:= -O3 -mavx2 -flto

LD_FLAGS 	:= -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR 	:= src
BUILD_DIR 	:= build
INCLUDE_DIR := include

SRC_FILES	:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES   := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

TARGET		:= mandelbrot.out

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LD_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/*.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o *.out
