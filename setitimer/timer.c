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

    // structure for setting up timer
    struct itimerval t_val;

    t_val.it_value.tv_sec = 5;  /* Interval for periodic timer */
    t_val.it_value.tv_usec = 0; /* Current value (time until next expiration) */
    t_val.it_interval = t_val.it_value;
    if (setitimer(ITIMER_REAL, &t_val, NULL) == -1)
    {
        perror("error calling setitimer()");
        exit(1);
    }

    printf("Timer has been set\r\n");

    struct itimerval current_timer_state;
    for (int i = 0; i < 60; ++i)
    {
        int tsleep = 1;
        // interrupt will break sleep function . check return value of the sleep function
        while (tsleep = sleep(tsleep))
        {
        }
        printf("process running ... %d \r\n", i + 1);
        if (getitimer(ITIMER_REAL, &current_timer_state) != 0)
        {
            perror("getitimer ");
        }
        else
        {
            printf("timer sec : %ld  usec : %ld\r\n", current_timer_state.it_value.tv_sec, current_timer_state.it_value.tv_usec);
        }
        printf("\r\n\r\n");
    }

    // struct for disable timer
    struct itimerval t_valdis = {
        .it_interval = {.tv_sec = 0, .tv_usec = 0},
        .it_value = {0, 0}};

    // disable timer
    if (setitimer(ITIMER_REAL, &t_valdis, NULL) < 0)
    {
        perror("setitimer");
        abort();
    }

    printf("Timer was disabled\r\n");
    return 0;
}