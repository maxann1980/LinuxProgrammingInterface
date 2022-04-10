#define _GNU_SOURCE

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define BUF_SIZE 200

int main(int argc, char **argv) {
  setbuf(stdout, NULL); /* Disable buffering of stdout */
  int pipefd[2];
  char buf[BUF_SIZE] = {0}; // each proces will has its own copy of buffer

  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(1);
  }

  switch (fork()) {
  case -1:
    perror("fork");
    exit(1);
    break;
  case 0: // child process
  {
    int nbytes;
    if (close(pipefd[WRITE]) < 0) {
      perror("close");
      exit(1);
    }
    while ((nbytes = read(pipefd[READ], buf, BUF_SIZE)) > 0) {
      printf("Process id : %d Received data from pipe: %s", getpid(), buf);
      memset(buf, 0, BUF_SIZE);
    }
    if (nbytes < 0) {
      perror("read");
    }
    if (close(pipefd[READ]) < 0) {
      perror("close");
      exit(1);
    }
  } break;
  default: // parent process
    if (close(pipefd[READ]) < 0) {
      perror("close");
      exit(1);
    }
    for (int i = 0; i < 5; ++i) {
      printf("Process pid % d tryes to send data to pipe\r\n", getpid());
      snprintf(buf, BUF_SIZE, "Hello from proc %d\r\n", getpid());
      int size = strlen(buf);
      if (write(pipefd[WRITE], buf, size) < 0) {
        perror("write");
        exit(1);
      }
      memset(buf, 0, BUF_SIZE);
      sleep(1);
    }
    if (close(pipefd[WRITE]) < 0) {
      perror("close");
      exit(1);
    }
    break;
  }
  return 0;
}
