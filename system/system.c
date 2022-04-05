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

void print_exit_code(int status) {
    if (WIFEXITED(status)) {
        printf("process exited with status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("process killed by signal %d (%s)", WTERMSIG(status), strsignal(WTERMSIG(status)));
    } else {
        printf(" unknown status=%x\n", (unsigned int)status);
    }
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL); /* Disable buffering of stdout */
    int status = system("ls");
    printf("system() returned: status=0x%04x (%d,%d)\n", (unsigned int)status, status >> 8, status & 0xff);
    if (status == -1) {
        perror("system");
        exit(1);
    } else {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
            printf("(Probably) could not invoke shell\n");
        else /* Shell successfully executed command */
            print_exit_code( status );
    }
    return 0;
}
