#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

// etext - next byte after end of programm text - > start of initialized data block
// edata - next byte after initialized data block - > start of uninitialized data block
// end   - next byte after uninitialized data segment
extern char etext, edata, end;

//The  variable environ points to an array of pointers to strings called the "environment". 
extern char **environ;

int main(int argc, char** argv) {
    pid_t proc_id = getpid();
    pid_t parent_id = getppid();

    printf("Process id : %d\r\n",proc_id);
    printf("Parrent id : %d\r\n",parent_id);

    printf("*****************************************\r\n");
    printf("etext : %10p\r\n",&etext);
    printf("edata : %10p\r\n",&edata);
    printf("end   : %10p\r\n\r\n",&end);

    printf ("size of uninitialized data : %ld \r\n", &end - &edata);
    printf ("size of initialized data : %ld\r\n", &edata - &etext);

    printf("*****************************************\r\n");
    // name of programm
    // program_invocation_short_name - extern variable from errno.h
    printf("%s\r\n",program_invocation_short_name);

    // program_invocation_name - extern variable from errno.h
    printf("%s\r\n",program_invocation_name);

    printf("*****************************************\r\n\r\n");
    printf("Enrironment variables\r\n");
    for(int i=0; environ[i] != NULL; ++i) {
        printf("%s\r\n",environ[i]);
    }
    return 0;
}