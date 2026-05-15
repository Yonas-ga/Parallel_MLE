# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++17 -O2 -Wall

# Try common Eigen install paths automatically
EIGEN_INC := $(shell \
    if [ -d /usr/include/eigen3 ]; then \
        echo /usr/include/eigen3; \
    elif [ -d /opt/homebrew/include/eigen3 ]; then \
        echo /opt/homebrew/include/eigen3; \
    elif [ -d /usr/local/include/eigen3 ]; then \
        echo /usr/local/include/eigen3; \
    else \
        $(warning "Eigen not found in common paths, set EIGEN_INC manually") \
        echo ""; \
    fi)

# Abort early if Eigen was not found
ifeq ($(EIGEN_INC),)
    $(error Eigen not found. Run: make EIGEN_INC=/path/to/eigen3)
endif

# Collect all .cpp files (excluding files that start with test_)
SRCS := $(wildcard *.cpp)
BINS := $(SRCS:.cpp=)

# Default target: build everything
all: $(BINS)

# Generic rule: any .cpp -> binary
%: %.cpp
	$(CXX) $(CXXFLAGS) -I$(EIGEN_INC) $< -o $@

# Run a specific target: make run TARGET=Baseline
run:
	@if [ -z "$(TARGET)" ]; then \
		echo "Usage: make run TARGET=<name>  (e.g. make run TARGET=Baseline)"; \
	else \
		./$(TARGET); \
	fi

# Print detected Eigen path (useful for debugging)
info:
	@echo "Eigen path : $(EIGEN_INC)"
	@echo "Sources    : $(SRCS)"
	@echo "Binaries   : $(BINS)"

clean:
	rm -f $(BINS) *.out

.PHONY: all run info clean