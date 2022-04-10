#define _GNU_SOURCE

#include <errno.h>
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

int main(int argc, char **argv) {
  setbuf(stdout, NULL); /* Disable buffering of stdout */
  pid_t server_pid = 0;

  if (mkfifo(SERVER_FIFO_COMMON, S_IRUSR | S_IWUSR | S_IWGRP) == -1 &&
      errno != EEXIST) {
    perror("mkfifo");
    exit(1);
  }
  printf(" FIFO created\r\n");

  // create server routine
  switch (server_pid = fork()) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
    break;
  case 0: {
    int res = system("./server");
    printf("COMMON : system - server result : %d\r\n", res);
    exit(EXIT_SUCCESS);
  } break;
  default:
    break;
  }

  // create clients for the server
  for (int i = 0; i < 5; ++i) {
    int res;
    switch (fork()) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    case 0:
      res = system("./client");
      printf("COMMON : system - client %d result : %d\r\n", i, res);
      exit(EXIT_SUCCESS);
      break;
    default:
      sleep(1);
      break;
    }
  }
  waitpid(server_pid,NULL,0);

  return 0;
}
