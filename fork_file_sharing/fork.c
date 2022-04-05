#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static int global_data = 111;

int main(int argc, char** argv) {
    pid_t child;
    int flags;
    char template[] = "tmp_file_XXXXXX";

    int fd = mkstemp(template);
    if (fd  < 0) {
        perror("mkstemp");
        exit(1);
    }

    printf("File offset before fork(): %lld\n",(long long) lseek(fd, 0, SEEK_CUR));
    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl - F_GETFL");
        exit(1);
    }

    printf("O_APPEND flag before fork() is: %s\n", (flags & O_APPEND) ? "on" : "off");

    switch (child = fork()) {
        case -1:
        break;
        case 0: // child process
            if (lseek(fd, 1000, SEEK_SET) == -1) {
                perror("lseek");
                _exit(EXIT_FAILURE);
            }
            flags = fcntl(fd, F_GETFL); /* Fetch current flags */
            if (flags == -1) {
                perror("fcntl - F_GETFL");
                _exit(EXIT_FAILURE);
            }
            flags |= O_APPEND; /* Turn O_APPEND on */
            if (fcntl(fd, F_SETFL, flags) == -1) {
                perror("fcntl - F_SETFL");
                _exit(EXIT_FAILURE);
            }
            _exit(EXIT_SUCCESS);
            break;
        default:
            if (wait(NULL) == -1) {
                perror("wait"); /* Wait for child exit */
                exit(EXIT_FAILURE);
            }
            printf("Child has exited\n");
            printf("File offset in parent: %lld\n",(long long)lseek(fd, 0, SEEK_CUR));
            flags = fcntl(fd, F_GETFL);
            if (flags == -1) {
                perror("fcntl - F_GETFL");
                exit(EXIT_FAILURE);
            }
            printf("O_APPEND flag in parent is: %s\n", (flags & O_APPEND) ? "on" : "off");
            exit(EXIT_SUCCESS);
            break;
    }
    return 0;
}