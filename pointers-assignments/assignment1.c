#include <stdio.h>

int main(void)
{
	int x = 10;
	int *ptr = &x;
	printf("Address using &x: %p\n", (void*)&x);
	printf("Address using ptr: %p\n", (void*)ptr);
	*ptr = 24;
	printf("new value of x: %d\n", x);

	return (0);
}


