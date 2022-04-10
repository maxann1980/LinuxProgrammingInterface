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

static int var = 0;
pthread_mutex_t mtx;

void *thread_function(void *params) {
  int counter = *((int *)params);
  for (int i = 0; i < counter; ++i) {
    int s = pthread_mutex_lock(&mtx);
    if (s != 0) {
      printf("%s\r\n", strerror(s));
      pthread_exit(NULL);
    }

    int int_var = var;
    ++int_var;
    var = int_var;
    s = pthread_mutex_unlock(&mtx);
    if (s != 0) {
      printf("%s\r\n", strerror(s));
      pthread_exit(NULL);
    }
  }
  return NULL;
}

int main(int argc, char **argv) {
  pthread_t thread1;
  pthread_t thread2;
  void *res;
  int iter_count = 1000000;

  int s = pthread_mutex_init(&mtx,NULL);
  if (s != 0) {
    printf("%s\r\n", strerror(s));
    exit(1);
  }

  s = pthread_create(&thread1, NULL, thread_function, (void *)&iter_count);
  if (s != 0) {
    printf("%s\r\n", strerror(s));
    exit(1);
  }

  s = pthread_create(&thread2, NULL, thread_function, (void *)&iter_count);
  if (s != 0) {
    printf("%s\r\n", strerror(s));
    exit(1);
  }

  s = pthread_join(thread1, &res);
  if (s != 0) {
    printf("%s\r\n", strerror(s));
    exit(1);
  }

  s = pthread_join(thread2, &res);
  if (s != 0) {
    printf("%s\r\n", strerror(s));
    exit(1);
  }

  s = pthread_mutex_destroy(&mtx);
  if (s != 0) {
    printf("%s\r\n", strerror(s));
    exit(1);
  }

  printf("var =  %d \r\n", var);
  return 0;
}
