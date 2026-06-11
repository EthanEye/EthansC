
# List of files
C_SOURCES = coordinator.c checker.c
C_OBJECTS = coordinator.o checker.o
EXE1 = coordinator
EXE2 = checker

# Compiler and loader commands and flags
GCC = gcc
GCC_FLAGS = -std=c11 -g -Wall -c -I.
LD_FLAGS  = -std=c11 -g -Wall -I.

# Compiles .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<

# Target is the executables: coordinator, checker
all: coordinator checker

# Builds coordinator executable
coordinator: coordinator.o
	$(GCC) $(LD_FLAGS) coordinator.o -o $(EXE1)

# Builds checker executable
checker: checker.o
	$(GCC) $(LD_FLAGS) checker.o -o $(EXE2)

# Cleans up object files and executables
clean:
	rm -f *.o *~ $(EXE1) $(EXE2)

# Packages directory files into .zip file
package:
	zip Eye-Ethan-HW3.zip coordinator.c checker.c Makefile README.txt