Ethan Eye - CS370 HW3 (Extra Credit)

Files:
- coordinator.c : Forks one checker per number. For each child, creates a
  private pipe and a private shared memory segment, writes the segment ID
  into the pipe, and passes the pipe's read-end fd as an exec argument.
  Waits on each child, reads its result from shared memory, and destroys
  each segment.
- checker.c : Reads the shared memory ID from the pipe, attaches, tests
  divisibility, writes 1 or 0 to shared memory, detaches.
- Makefile : 'make all' builds both programs, 'make clean' removes binaries.

Usage: ./coordinator <divisor> <num1> <num2> <num3> <num4>