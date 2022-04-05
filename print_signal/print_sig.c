#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int f(a, b)int a; float b; {
    printf("%d %f \r\n", a, b);
}

int main(int argc, char** argv) {
    for ( int i=1; i < __SIGRTMAX; ++i ) {
        printf("SIGNAL %d - %s\r\n",i,strsignal(i));
    }
    f(1,20);
    return 0;
}