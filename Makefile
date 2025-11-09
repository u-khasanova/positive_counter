# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3
LDFLAGS := -pthread

# Default targets
.PHONY: all clean release debug parallel linear single test info

# Executable name
TARGET := positive_counter

# Directories
SRCDIR := src
OBJDIR := obj
BINDIR := bin

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Main target - parallel version
all: $(BINDIR)/$(TARGET)

# Ensure directories exist before compiling
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# Build executable
$(BINDIR)/$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Parallel version (default)
parallel: CXXFLAGS += -DPARALLEL_MODE
parallel: clean all

# Linear version
linear: CXXFLAGS += -DLINEAR_MODE
linear: clean all

# Auto-detect cores
auto_cores: CXXFLAGS += -DAUTO_CORES
auto_cores: clean all

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Build targets info
info:
	@echo "Available build targets with -D flags:"
	@echo "  all         - standard build (parallel)"
	@echo "  parallel    - parallel version (-DPARALLEL_MODE)"
	@echo "  linear      - linear version only (-DLINEAR_MODE)"
	@echo "  auto_cores  - auto-detect cores (-DAUTO_CORES)"
	@echo ""
	@echo "Examples:"
	@echo "  make linear && ./bin/positive_counter	        # Build linear version"
	@echo "  make linear && ./bin/positive_counter 4	    # Works in linear mode ignoring num_threads"
	@echo "  make parallel && ./bin/positive_counter 4		# 4 threads"
	@echo "  make auto_cores && ./bin/positive_counter      # Auto-detect CPU cores"
	@echo "  make clean                     				# Clean build artifacts"
	@echo ""
	@echo "Usage examples:"
	@echo "  ./bin/positive_counter 4       				# Use 4 threads (parallel mode)"