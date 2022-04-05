#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void exit_handler1(void) {
    // do some clean work
    printf("exit_handler1\r\n");
}

void exit_handler2(void) {
    // do some clean work
    printf("exit_handler2\r\n");
}



int main(int argc, char** argv) {
    // register 1 handler 
    if ( atexit(exit_handler1) ) {
        perror("atexit 1");
    }

    // register 2 handler 
    if ( atexit(exit_handler2) < 0) {
        perror("atexit 2");
    }

    for (int i=0; i < 3; ++i) {
        printf("process working\r\n");
        sleep(1);
    }
    return 0;
}