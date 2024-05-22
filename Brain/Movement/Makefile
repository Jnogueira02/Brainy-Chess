# Compiler settings - Can change cc to clang++ or another compiler if desired
CC = g++ 
CFLAGS = -Wall -O2 -g
# Executable name
EXE = blockedMovement

# List all object files here
OBJS = blockedMovement.o diagonalMovement.o horizontalVerticalMovement.o knightMovement.o

# Default target
all: $(EXE)

# Linking the executable from the object files
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling blockedMovement program
blockedMovement.o: blockedMovement.cpp diagonalMovement.hpp horizontalVerticalMovement.hpp knightMovement.hpp
	$(CC) $(CFLAGS) -c blockedMovement.cpp

# Compiling support programs
diagonalMovement.o: diagonalMovement.cpp diagonalMovement.hpp
	$(CC) $(CFLAGS) -c diagonalMovement.cpp

horizontalVerticalMovement.o: horizontalVerticalMovement.cpp horizontalVerticalMovement.hpp
	$(CC) $(CFLAGS) -c horizontalVerticalMovement.cpp

knightMovement.o: knightMovement.cpp knightMovement.hpp
	$(CC) $(CFLAGS) -c knightMovement.cpp

# Clean up
clean:
	rm -f *.o $(EXE)

# Phony targets
.PHONY: all clean
