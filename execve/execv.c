#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char **argv) {
    setbuf(stdout, NULL); /* Disable buffering of stdout */

    printf("create child thread \r\n");
    pid_t child;
    switch (child = fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            printf("child process create new process with DATE \r\n");
            char* argv[] = {"/usr/bin/date",NULL};
            execve(argv[0], argv, environ);
            // we can be here in case execve failed
            perror("execve failed");
            exit(1);
            break;
        default: {
            int status;
            int ch_pid = wait(&status);
            if (ch_pid == -1) {
                if (errno == ECHILD) {
                    printf("No more children\n");
                    exit(EXIT_SUCCESS);
                } else { /* Some other (unexpected) error */
                    perror("wait");
                    exit(1);
                }
            }
            if (WIFEXITED(status)) {
                printf("child exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("child killed by signal %d (%s)", WTERMSIG(status), strsignal(WTERMSIG(status)));
            } else if (WIFSIGNALED(status)) {
                printf("child killed by signal %d (%s)", WTERMSIG(status), strsignal(WTERMSIG(status)));
            } else {
                printf("what happened to this child? (status=%x)\n", (unsigned int)status);
            }
        } break;
    }
    return 0;
}
