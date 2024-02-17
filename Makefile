CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -Iinclude
EXECUTABLE=main

OBJ=main lattice cell

all: src/main.cc $(OBJ:%=build/%.o)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $^

build/%.o: src/%.cc include/%.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o build/$*.o src/$*.cc

clean:
	rm -rf build/*.o 
	rm -f $(EXECUTABLE)
	@echo "Cleaned up"

.PHONY: clean