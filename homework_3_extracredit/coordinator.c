#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Ethan Eye Homework 2
// pid_t is a data type for process IDs it is the same as a int just for
// readability meaning (process ID type). POSIX only (large set of libaries for
// multiprocessing and multithreading)

int main(int argc, char *argv[]) {
  if (argc != 6) {
    printf("Coordinator: invalid arguments\n");
    return 1;
  }

  // parent needs to write shared memory to a pipe
  // and pass a reference to the read end of the pipe and then call execlp

  // creates an array of two file descriptors
  // let kernal fill it in with pipe()
  // fds is a way the kernal can mediate communication of other things outside
  // of the process. (a file, pipe, socket, a terminal, i/o devices) every
  // process starts with 3 default fds in unix stdin, stdout, stderr

  int fd[2];
  pipe(fd);
  int numChildren = argc - 2;
  int shmIds[numChildren];
  pid_t pids[numChildren];

  for (int i = 0; i < numChildren; i++) {
    shmIds[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmIds[i] < 0) {
      perror("shmget");
      return 1;
    }

    int fd[2];
    if (pipe(fd) < 0) {
      perror("pipe");
      return 1;
    } // one pipe per child

    pids[i] = fork();
    if (pids[i] < 0) {
      perror("fork");
      return 1;
    }
    if (pids[i] == 0) {
      close(fd[1]);
      char fdBuf[12];
      sprintf(fdBuf, "%d", fd[0]);
      execlp("./checker", "checker", argv[1], argv[i + 2], fdBuf, NULL);
      perror("execlp");
      exit(1);
    }
    printf("Coordinator: forked process with ID %d.\n", pids[i]);
    write(fd[1], &shmIds[i], sizeof(int));
    printf("Coordinator: wrote shm ID %d to pipe (4 bytes)\n", shmIds[i]);
    close(fd[0]);
    close(fd[1]); // parent done with this pipe
  }

  for (int i = 0; i < numChildren; i++) {
    printf("Coordinator: waiting on child process ID %d...\n", pids[i]);
    waitpid(pids[i], NULL, 0);
    int *res = (int *)shmat(shmIds[i], NULL, 0);
    if (res == (int *)-1) {
      perror("shmat");
      return 1;
    }
    printf("Coordinator: result %d read from shared memory: %s is %sdivisible "
           "by %s.\n",
           *res, argv[i + 2], *res ? "" : "not ", argv[1]);
    shmdt(res);
    shmctl(shmIds[i], IPC_RMID, NULL);
  }
  printf("Coordinator: exiting.\n");
  return 0;
}