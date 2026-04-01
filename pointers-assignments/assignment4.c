#include <stdio.h>
int main(void)
{
	int x = 10;
	int *ptr = &x;
	int **dptr = &ptr;
	printf("ptr: %d\n", *ptr);
	printf("dptr: %d\n", **dptr);
}

