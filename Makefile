# List all source files
SRCS := $(wildcard *.cpp)
SRCS += $(wildcard */*.cpp)  # Include source files from subdirectories

# List all header files
HEADERS := $(wildcard *.h)
HEADERS += $(wildcard */*.h)  # Include header files from subdirectories

# Compiler
CXX := clang++

# Compiler flags
override CXXFLAGS += -g -Wmost -Werror

# Target for the main executable
main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

# Clean up
clean:
	rm -f main