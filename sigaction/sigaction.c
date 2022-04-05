#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void sig_handler(int var) {
    printf("Signal handler: %s\r\n",strsignal(var)); /* !!!  UNSAFE  !!! */
}

int main(int argc, char** argv) {
    struct sigaction new_sigact ;
    struct sigaction old_sigact;

    new_sigact.sa_handler = sig_handler;
    sigemptyset (&new_sigact.sa_mask);
    new_sigact.sa_flags = 0;

    if ( -1 == sigaction (SIGINT, &new_sigact, &old_sigact)) {
        perror("sigaction");
        abort();
    }

    if ( -1 == sigaction (SIGCHLD, &new_sigact, &old_sigact)) {
        perror("sigaction");
        abort();
    }

    if ( -1 == sigaction (SIGUSR1, &new_sigact, &old_sigact)) {
        perror("sigaction");
        abort();
    }

    printf("My pid : %d\r\n",getpid());

    pause();


    return 0;
}