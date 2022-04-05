#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int global_data = 111;

int main(int argc, char** argv) {
    pid_t child;
    int stack_data = 222;
    printf("Parent pid : %d\r\n",getpid());

    switch (child = fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:  // child process
            global_data *= 3;
            stack_data *= 3;
            break;
        default:  // parent process
            break;
    }

    printf ("Process pid %d. global_data : %d  stack_data : %d\r\n",getpid(),global_data, stack_data);
    return 0;
}