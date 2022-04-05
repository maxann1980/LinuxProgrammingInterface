#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

const int children = 5;

int main(int argc, char **argv) {
    setbuf(stdout, NULL); /* Disable buffering of stdout */

    printf("parent process with pid : %d started\r\n", getpid());

    for (int i = 0; i < children; ++i) {
        switch (fork()) {
            case -1:
                perror("fork");
                break;
            case 0:  // child
                printf("child with pid %d was created\r\n", getpid());
                sleep(i);
                exit(i);
                break;
            default:
                break;
        }
    }
    int status;
    for (int i = 0; i < children;) {
        int ch_pid = wait(&status);
        if (ch_pid == -1) {
            if (errno == ECHILD) {
                printf("No more children - bye!\n");
                exit(EXIT_SUCCESS);
            } else { /* Some other (unexpected) error */
                perror("wait");
                exit(1);
            }
        }
        printf("wait returned child PID %d  ", ch_pid);
        if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("child killed by signal %d (%s)",  WTERMSIG(status), strsignal(WTERMSIG(status)));
        } else {
            printf("what happened to this child? (status=%x)\n",(unsigned int) status);
        }
        ++i;
    }

    return 0;
}