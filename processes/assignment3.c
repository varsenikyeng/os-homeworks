#include <stdio.h>
#include <stdlib.h>

void out1(void) {
    printf("atexit succeded from function 1 \n");
}
void out2(void) {
    printf("atexit succeded from function 2 \n");
}

int main()
{
    int x; 
    float f; 
    f = (float)x;
    
    if(atexit(out1)){
        fprintf(stderr, "atexit failed for out1\n");
    }

    if(atexit(out2)){
        fprintf(stderr, "atexit failed for out2\n");
    }

    printf("Hello world \n");
    exit(0);
    printf("Process...\n");
}