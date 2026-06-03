# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++17 -O2 -Wall

# Collect all .cpp files (excluding files that start with test_)
SRCS := $(wildcard *.cpp)
BINS := $(SRCS:.cpp=)

# Default target: build everything
all: $(BINS)

# Generic rule: any .cpp -> binary
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Run a specific target: make run TARGET=Baseline
run:
	@if [ -z "$(TARGET)" ]; then \
		echo "Usage: make run TARGET=<name>  (e.g. make run TARGET=Baseline)"; \
	else \
		./$(TARGET); \
	fi

# Print detected Eigen path (useful for debugging)
info:
	@echo "Sources    : $(SRCS)"
	@echo "Binaries   : $(BINS)"

clean:
	rm -f $(BINS) *.out

.PHONY: all run info clean