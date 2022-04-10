#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define SERVER_FIFO_COMMON "fifo_server"
#define BUF_SIZE 200

int main(int argc, char **argv) {
  setbuf(stdout, NULL); /* Disable buffering of stdout */
  char buf[BUF_SIZE] = {0};

  printf("Client id %d working... \r\n", getpid());

  printf("Client id %d : try to open fifo\r\n", getpid());

  int fifo_fd = open(SERVER_FIFO_COMMON, O_WRONLY);
  if (fifo_fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  /*  Ignore the SIGPIPE signal, so that if the server attempts to write to a
      client FIFO that doesn’t have a reader, then, rather than being sent a
     SIGPIPE signal (which kills a process by default), it receives an EPIPE
     error from the write() system call.
  */
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("signal");
  }

  // server always work
  for (int i = 0; i < 5; ++i) {
    snprintf(buf, BUF_SIZE, "Client %d msg %d\r\n", getpid(), i);
    int size = strlen(buf);
    if ( write(fifo_fd, buf, size) != size ) {
      perror("write");
      exit(EXIT_FAILURE);
    }
    sleep(1);
  }
  return 0;
}
