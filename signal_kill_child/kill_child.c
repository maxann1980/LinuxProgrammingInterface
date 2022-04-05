#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int child_state = 1;

void signal_handler(int sig) {
    switch (sig) {
        case SIGCHLD:
        printf("received : %s\r\n",strsignal(sig));
        child_state = 0;
        break;
        case SIGINT:
            printf("received : %s\r\n",strsignal(sig));
            child_state = 0;
        break;
        default:
        break;
    }
}

int main(int argc, char** argv) {

    if (SIG_ERR == signal(SIGCHLD,signal_handler)) {
        perror("signal disposition failed!");
        exit(1);
    }

    if (SIG_ERR == signal(SIGINT,signal_handler)) {
        perror("signal disposition failed!");
        exit(1);
    }

    printf("Programm started !\r\n");
    int res = fork();
    if (res > 0) {
        //parent process
        printf ("Child process with pid %d created\r\n",res);
        for(int i=0; i < 5; ++i) {
            printf("Parent process working . My proc id : %d\r\n",getpid());
            sleep(1);
        }

        printf("Send kill signal to child : %d\r\n",res);
        if (-1 == kill(res,SIGINT) ){
            perror("kill failed");
            exit(1);
        }
        while(child_state)
            sleep(1);

    } else if (res ==0){
        // child process
        for (int i=0; i < 100 && child_state; ++i) {
            printf("Child process working . My proc id : %d\r\n",getpid());
            sleep(1);
        }
    } else {
        perror("Fork failed.");
        exit(1);
    }

    printf("Process %d finished\r\n", getpid());
    return 0;
}