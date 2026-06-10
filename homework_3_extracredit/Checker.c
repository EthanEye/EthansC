#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    // pipe stuff extract shared mem id ...
    // process receive the read end of the pipe
    // put the reference in a local variable 
    int sharedMemId = 0;
    // get a pointer to shared memory and attach to the segment
    int *sharedMemPointer = (int *)shmat(sharedMemId, NULL, 0);
    // write to shared memory
    // increment mem pointer to add more data 
    // + 1 moves towards higher address -1 moves towards lower address 4 bytes
    
    // do some math and write either a 1 or a 0 to shared memory segment
    *sharedMemPointer = 1;
    //detatch
    //schmdt(sharedMemPointer);

    printf("Checker process [%d]: Starting.\n", getpid());

    if (atoi(argv[2]) % atoi(argv[1]) == 0)
    {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), atoi(argv[2]), atoi(argv[1]));
        printf("Checker process [%d]: Returning 0.\n", getpid());
        return 1;
    }
    else
    {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), atoi(argv[2]), atoi(argv[1]));
    }   
    printf("Checker process [%d]: Returning 1.\n", getpid());
    return 0;
}