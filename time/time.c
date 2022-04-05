#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#define BUF_SIZE    100

int main(int argc, char **argv)
{
    struct timeval timestamp = {
        .tv_sec = 0,  /* Seconds since 00:00:00, 1 Jan 1970 UTC */
        .tv_usec = 0, /* Additional microseconds (long int) */
    };

    gettimeofday(&timestamp, NULL);

    printf("seconds %ld\r\n",timestamp.tv_sec);

    char *c_time = ctime(&timestamp.tv_sec);
    printf ("ctime : %s\r", c_time);

    struct tm* s_time = localtime(&timestamp.tv_sec);
    printf("seconds         : %d\r\n", s_time->tm_sec);
    printf("minutes         : %d\r\n", s_time->tm_min);
    printf("hours           : %d\r\n", s_time->tm_hour);
    printf("day of month    : %d\r\n", s_time->tm_mday);
    printf("Month           : %d\r\n", s_time->tm_mon + 1 );
    printf("Year            : %d\r\n", s_time->tm_year + 1900);
    printf("day of week     : %d\r\n", s_time->tm_wday);
    printf("day of year     : %d\r\n", s_time->tm_yday + 1);
    printf("daylight        : %d\r\n", s_time->tm_isdst);

    char* t_string = asctime(s_time);
    printf("asctime : %s\r\n",t_string);

    // print formated  date time
    char buf[BUF_SIZE] = {0};
    strftime(buf,BUF_SIZE,"%Y %B %A %H:%M:%S",s_time);
    printf("strftime : %s\r\n",buf);


    //convert struct tm to time_t
    time_t conv_time = mktime(s_time);
    printf("seconds %ld\r\n",conv_time);

    return 0;
}