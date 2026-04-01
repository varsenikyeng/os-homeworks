#include <stdio.h>
int main(void)
{
	char str[] = "Hello";
	char *p = str;
	while(*p)
	{
		putchar(*p);
		p++;
	}
	printf("\n");
	p = str;
	int i = 0;
	while(*p)
	{
		p++;
		i++;
	}
	printf("length : %d", i);
}
