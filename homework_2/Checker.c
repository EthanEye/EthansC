#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

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