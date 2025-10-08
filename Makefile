CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Object files
sv128.o: sv128.cpp sv128.h sv_logger.h
	$(CXX) $(CXXFLAGS) -c sv128.cpp

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

.PHONY: all clean