#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

// Ethan Eye Homework 2
// pid_t is a data type for process IDs it is the same as a int just for readability meaning (process ID type).
// POSIX only (large set of libaries for multiprocessing and multithreading)

int main(int argc, char *argv[])
{

    
    for (int i = 2; i < argc; i++)
    {
        char *args[] = {"checker", argv[1], argv[i], NULL};
        pid_t pid = fork();
        // run only for child processes
        if (pid == 0)
        {
            printf("Process %d created\n", getpid());
            execvp("./checker", args);
            exit(0);
        }
    }
    // only ran my parent process
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
        printf("Process %d finished\n", getpid());
    }

    return 0;
}