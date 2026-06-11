
# Homework 2 CS370
# Ethan Eye


## Compile

gcc -Wall -o coordinator Coordinator.c
gcc -Wall -o checker Checker.c

## Command

 > ./coordinator 3 8 15 21 20

## Coordinator

The coordinator class creates a child process with fork() for each dividend. The parent process will wait for child process to execute the Checker program.

## Checker

Once the child process is spawned, execlp() is called and the process runs the Checker program with argc and the arguments containing the dividend and divisor. If the modulus is zero the numbers are divisable and it returns zero, other wise it returns 1. 

## Final output

After the parent process calls wait(&status). The parent waits for the child to finish execution. The exit status is obtain by WEXITSTATUS(status); which is then printed to the console as either a 0 meaning it is divisable or a 1 meaning its not divisable. 
