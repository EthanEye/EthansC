#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

// checker: receives the pipe's read end as an argument, reads the shared
// memory ID from the pipe, attaches, writes its result (1 or 0), detaches.
int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Checker: invalid number of arguments\n");
        return 1;
    }

    // the pipe's read end, passed as text through exec
    int readfd = atoi(argv[3]);

    // read the shared memory ID from the pipe (raw bytes)
    int sharedMemId;
    ssize_t n = read(readfd, &sharedMemId, sizeof(sharedMemId));
    if (n != sizeof(sharedMemId)) {
        perror("Checker: read");
        return 1;
    }
    close(readfd);

    printf("Checker process [%d]: starting.\n", getpid());
    printf("Checker process [%d]: read %zd bytes containing shm ID %d\n",
           getpid(), n, sharedMemId);

    // attach to this child's own shared memory segment
    int *sharedMemPointer = (int *)shmat(sharedMemId, NULL, 0);
    if (sharedMemPointer == (int *)-1) {
        perror("Checker: shmat");
        return 1;
    }

    // do the math: 1 if divisible, 0 if not
    int divisor = atoi(argv[1]);
    int num     = atoi(argv[2]);
    int result  = (num % divisor == 0);

    printf("Checker process [%d]: %d *IS%s* divisible by %d.\n",
           getpid(), num, result ? "" : " NOT", divisor);

    // write the result to shared memory for the coordinator to read
    *sharedMemPointer = result;
    printf("Checker process [%d]: wrote result (%d) to shared memory.\n",
           getpid(), result);

    // detach from the segment (coordinator destroys it)
    shmdt(sharedMemPointer);
    return 0;
}