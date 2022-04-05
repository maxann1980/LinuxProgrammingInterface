#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_SIZE  5
#define ARRAY_SIZE  100

// etext - next byte after end of programm text - > start of initialized data block
// edata - next byte after initialized data block - > start of uninitialized data block
// end   - next byte after uninitialized data segment
extern char _etext, _edata, _end;

void useless_function() {
    printf("stack pointer : %10p\r\n",alloca(0));
    // allocation af memory
    int* ar = malloc(ARRAY_SIZE*sizeof(int));
    ar++;
}


int main(int argc, char** argv) {

    // current stack pointer
    printf("main stack pointer : %10p\r\n\r\n",alloca(0));

    // meamory leak
    useless_function();

    void* begin = sbrk(0);
    printf("Address of first byte after bss block : %10p\r\n",&_end);

    // address for programm break will start from new page!
    printf("Initial programm break      : %10p\r\n",begin);
    printf("Allocate memory for array of int[100] \r\n");
    int* array = malloc( ARRAY_SIZE * sizeof(int));
    for (int i=0; i < PRINT_SIZE; ++i) {
        printf("val[%d] = %d\r\n",i,array[i]);
    }
    printf("New programm break address  : %10p\r\n",sbrk(0));

    printf("Free memory\r\n");
    free(array);
    array = NULL;
    printf("New programm break address  : %10p\r\n",sbrk(0));

    
    printf("Allocate memory for array of int[100] \r\n");
    array = malloc(ARRAY_SIZE*sizeof(int));
    printf("New programm break address  : %10p\r\n",sbrk(0));
    free(array);
    array = NULL;

    // allocation memory and setting up all values to 0
    int* arr = calloc(100,sizeof(int));
    for (int i=0; i < PRINT_SIZE; ++i) {
        printf("val[%d] = %d\r\n",i,arr[i]);
    }




    return 0;
}