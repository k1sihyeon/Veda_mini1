CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = app

# SRCS = main.cpp order.cpp ordermanager.cpp client.cpp product.cpp
SRCS = $(wildcard *.cpp)

BUILD_DIR = build

# Object files
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cpp=.o)))

all: $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Rule to build object files with explicit dependencies
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

rebuild: clean all
