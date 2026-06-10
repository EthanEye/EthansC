#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Ethan Eye Homework 2
// pid_t is a data type for process IDs it is the same as a int just for readability meaning (process ID type).
// POSIX only (large set of libaries for multiprocessing and multithreading)

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Coordinator: invalid arguments\n");
        return 1;
    }

    // create shared memory segment (its seperate from all processes)
    int sharedMemId = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0666 );
    
    // parent needs to write shared memory to a pipe
    // and pass a reference to the read end of the pipe and then call execlp

    for (int i = 2; i < argc; i++)
    {
        if (atoi(argv[i]) < 0)
        {
            printf("Coordinator: invalid arguments\n");
            return 1;
        }
        
        
        // fork spawns new child process
        pid_t pid = fork();
       

        // run only for child processes
        if (pid == 0)
        {
            // get shared memory to child somehow 
            // using pipes
            // using execlp
            execlp("./checker", "checker", argv[1], argv[i], NULL);
            exit(0);
        }
        // for parent process
        else 
        {
            
            printf("Coordinator: forked process with ID %d.\n", pid);
            printf("Coordinator: waiting for process [%d].\n", pid);
            int status;
            // still wait for child to finish

            wait(&status);
            // parent should attach to shared memory segment after the children finish 
            // then parent should read from shared memory segment
            printf("Coordinator: child process %d returned %d.\n", pid, WEXITSTATUS(status));
          
        }
    }
    // destroy shared memory segment
    // shmctl(*sharedMemPointer, IPC_RMID, NULL);
    printf("Coordinator: exiting.\n");
    return 0;
}