CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Installation prefix - can be overridden with: make install PREFIX=/custom/path
PREFIX ?= /usr/local

# Implementation selection: SCALAR (default), SSE, or AVX
# Usage:
#   make                 (builds the scalar version)
#   make IMPL=SSE       (builds the SSE version)
#   make IMPL=AVX       (builds the AVX version)
IMPL ?= SCALAR

# Set implementation-specific flags and source files
ifeq ($(IMPL),SSE)
    CXXFLAGS += -msse4.1 -D_SSE_
    SV128_SRC = sv128_sse.cpp
else ifeq ($(IMPL),AVX)
    CXXFLAGS += -mavx -mavx2 -D_AVX_
    SV128_SRC = sv128_avx.cpp
else
    # Default to SCALAR implementation
    SV128_SRC = sv128_scalar.cpp
endif

# Object files
sv128.o: $(SV128_SRC) sv128.h sv_logger.h
	$(CXX) $(CXXFLAGS) -c $(SV128_SRC) -o sv128.o

sv_logger.o: sv_logger.cpp sv_logger.h sv128.h
	$(CXX) $(CXXFLAGS) -c sv_logger.cpp

# Static library
libsv128.a: sv128.o sv_logger.o
	ar rcs libsv128.a sv128.o sv_logger.o

# Main object file
main.o: main.cpp sv128.h sv_logger.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Test application
test_app: main.o libsv128.a
	$(CXX) $(CXXFLAGS) -o test_app main.o libsv128.a

# Build all
all: test_app

# Clean build artifacts
clean:
	rm -f *.o *.a test_app

# Display current implementation info
info:
	@echo "Current implementation: $(IMPL)"
	@echo "Source file: $(SV128_SRC)"
	@echo "Compiler flags: $(CXXFLAGS)"

# Install library and headers
install: libsv128.a
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include/sv128
	cp libsv128.a $(PREFIX)/lib/
	cp sv128.h sv_logger.h $(PREFIX)/include/sv128/

# Uninstall library and headers
uninstall:
	rm -f $(PREFIX)/lib/libsv128.a
	rm -rf $(PREFIX)/include/sv128

.PHONY: all clean install uninstall info