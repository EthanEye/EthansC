#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    printf("Checker: running checker %d\n", getpid());
    printf("Checker: dividend =  %s\n", argv[2]);
    printf("Checker: divisor = %s\n", argv[1]);

    if (atoi(argv[2]) % atoi(argv[1]) == 0)
    {
        return 0;
    }

    return 1;
}