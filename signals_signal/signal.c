#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define PRINT_SIZE  5
#define ARRAY_SIZE  100


// signal send from terminal 
// kill -17 "process_id"
static int sig_counter = 0;

void sig_handler(int var) {
    printf("Signal handler: %s\r\n",strsignal(var)); /* !!!  UNSAFE  !!! */
    if (++sig_counter > 5)
        exit(0);
}

void (*prev_sig_handler)(int var) = NULL;

int main(int argc, char** argv) {
    // save this value to restore previous desposition of signal
    prev_sig_handler = signal(SIGCHLD,sig_handler);
    printf("Process id : %d\r\n", getpid());
    
    for (int i=0; i < 60; ++i) {
        sleep(1);
        printf("process running ... %d \r\n",i+1);
    }
    return 0;
}