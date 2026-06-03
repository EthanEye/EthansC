#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{

printf("Running checker %d\n", getpid());
return 0;
}