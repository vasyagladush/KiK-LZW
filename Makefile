# Compiler
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17  

# Source files
SRCS = $(shell find src -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = lzw_compressor.out

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
