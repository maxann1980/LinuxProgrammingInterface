#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#define INTERVAL 500 /* number of milliseconds to go off */

static const char *sig_text = "Timer signal received\r\n\r\n";

void sig_handler(int var)
{
    write(STDOUT_FILENO, sig_text, strlen(sig_text));
}

int main(int argc, char **argv)
{
    // set disposition of signal
    struct sigaction temp;
    memset(&temp, 0, sizeof(temp));
    temp.sa_handler = &sig_handler;
    sigfillset(&temp.sa_mask);
    sigdelset(&temp.sa_mask, SIGINT);
    sigaction(SIGALRM, &temp, NULL);

    // set one shot timer to 2 seconds
    alarm(2);
    printf("Timer has been set\r\n");

    unsigned int tsleep = 5;
    // interrupt will break sleep function . check return value of the sleep function
    while (tsleep = sleep(tsleep)){}

    // stop axisting timer
    alarm(0);

    // set new timer value
    alarm(10);

    struct itimerval current_timer_state;
    for (int i = 0; i < 60; ++i)
    {
        int tsleep = 1;
        // interrupt will break sleep function . check return value of the sleep function
        while (tsleep = sleep(tsleep))
        {
        }
        printf("process running ... %d \r\n", i + 1);
        printf("\r\n\r\n");
    }
    return 0;
}