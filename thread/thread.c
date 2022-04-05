#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

extern char **environ;

void* thread_function(void* params) {
    printf("Thread id %ld pthread_self()\r\n", pthread_self());
    printf("Thread id %d gettid()\r\n", gettid());
    printf("Received params: %s \r\n",(char*)params);
    return (void*)strlen((char*)params);
}

int main(int argc, char **argv) {
    pthread_t thread;
    void* res;
    int s = pthread_create(&thread, NULL,thread_function, "Function params\n");
    if ( s!=0 ) {
        printf("%s\r\n",strerror(s));
        exit(1);
    }
    printf("main thread Ok. Sub thread created\r\n");
    s = pthread_join(thread,&res);
    if (s !=0 ) {
        printf("%s\r\n",strerror(s));
        exit(1);
    }

    printf("Thread returned value %ld\r\n",(long) res);
    return 0;
}
