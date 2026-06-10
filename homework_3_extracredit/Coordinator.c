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
    if (argc != 6)
    {
        printf("Coordinator: invalid arguments\n");
        return 1;
    }

    for (int i = 2; i < argc; i++)
    {
        if (atoi(argv[i]) < 0)
        {
            printf("Coordinator: invalid arguments\n");
            return 1;
        }

        // create a child process
        pid_t pid = fork();

        // run only for child processes
        if (pid == 0)
        {
            execlp("./checker", "checker", argv[1], argv[i], NULL);
            exit(0);
        }
        else
        {
            printf("Coordinator: forked process with ID %d.\n", pid);
            printf("Coordinator: waiting for process [%d].\n", pid);
            int status;
            wait(&status);
            printf("Coordinator: child process %d returned %d.\n", pid, WEXITSTATUS(status));
          
        }
    }
    printf("Coordinator: exiting.\n");
    return 0;
}