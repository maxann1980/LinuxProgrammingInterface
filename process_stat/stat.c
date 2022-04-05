#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char** argv) {
    printf("programm started\r\n\r\n");
    printf("try to find existed proc id\r\n");
    
    pid_t mpid = getpid();
    pid_t fpid = 0;
    bool found = false;

    for (int i=0; i < 1000; ++i) {
        fpid = rand() % mpid;
        int res = kill(fpid,0);
        if ( (res < 0  && errno == EPERM) || res >= 0) {
            printf("Process id exists : %d\r\n", fpid );
            found = true;
            break;
        } 
    }

    if ( found ) {
        struct stat statbuf;
        char path[30] = {0};
        snprintf(path,30,"/proc/%d",fpid);
        printf("proc path : %s\r\n",path);
        if ( stat(path, &statbuf) == 0 ) {
            printf("ID of device containing file    : %ld\r\n",(long int)statbuf.st_dev);
            printf("Inode number                    : %ld\r\n",(long int)statbuf.st_ino);
            printf("File type and mode              : %ld\r\n",(long int)statbuf.st_mode);
            printf("Number of hard links            : %ld\r\n",(long int)statbuf.st_nlink);
            printf("User ID of owner                : %ld\r\n",(long int)statbuf.st_uid);
            printf("Group ID of owner               : %ld\r\n",(long int)statbuf.st_gid);
            printf("Total size, in bytes            : %ld\r\n",(long int)statbuf.st_size);
        } else {
            perror("stat failed");
            exit(1);
        }
    } else {
        printf("Failed to find process id\r\n");
    }

    return 0;
}
