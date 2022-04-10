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

  printf("server working\r\n");

  int fifo_fd = open(SERVER_FIFO_COMMON, O_RDONLY);
  if (fifo_fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

    printf("Server: open fifo SUCCESS \r\n");
  /*  Ignore the SIGPIPE signal, so that if the server attempts to write to a
      client FIFO that doesn’t have a reader, then, rather than being sent a
     SIGPIPE signal (which kills a process by default), it receives an EPIPE
     error from the write() system call. But in this case server only reads data
     from fifo.
  */
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("signal");
  }

    // server always work
  while (1) {
    int res;
    if ( (res = read(fifo_fd, buf, BUF_SIZE)) < 0 ) {
      perror("Server read");
      exit(EXIT_FAILURE);
    }
    if (res > 0)
        printf("Server received data: %s", buf);
    else
        break;
  }

  return 0;
}
