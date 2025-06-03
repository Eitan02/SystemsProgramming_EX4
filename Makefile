# eitan.derdiger@gmail.com

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g
INCLUDE_DIR := include

# Source files
SRC := Demo.cpp

# Test source files (only test_core.cpp defines DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
TEST_SRCS := \
	tests/test_core.cpp \
	tests/test_order.cpp \
	tests/test_ascending.cpp \
	tests/test_descending.cpp \
	tests/test_reverse.cpp \
	tests/test_sidecross.cpp \
	tests/test_middleout.cpp \
	tests/test_exceptions.cpp \
	tests/test_snapshot.cpp

# Executable names
MAIN_EXE := main_demo
TEST_EXE := test_container

.PHONY: all Main test valgrind clean

all: $(MAIN_EXE) $(TEST_EXE)

# Build the main demonstration program
$(MAIN_EXE): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(SRC) -o $(MAIN_EXE)

# Build and link unit tests into a single test executable
$(TEST_EXE): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(TEST_SRCS) -o $(TEST_EXE)

# Run the demo
Main: $(MAIN_EXE)
	./$(MAIN_EXE)

# Run unit tests
test: $(TEST_EXE)
	./$(TEST_EXE)

# Check for memory leaks using valgrind
valgrind: $(TEST_EXE)
	valgrind --leak-check=full --error-exitcode=1 ./$(TEST_EXE)

# Clean build artifacts
clean:
	rm -f $(MAIN_EXE) $(TEST_EXE)
