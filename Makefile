# config
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -MMD -MP -g

# Change this to whatever you want your binary to be called
TARGET := main

# All .cpp files in the current directory
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEPS := $(OBJ:.o=.d)

# default target
all: $(TARGET)

# Link step: only runs if some .o changed
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

# Compile step: only runs for changed .cpp (or if headers they depend on changed)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include auto-generated dependency files for headers
-include $(DEPS)

# utilities
.PHONY: clean
clean:
	rm -f $(OBJ) $(DEPS) $(TARGET)
