#include <stdio.h>
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int main(void)
{
	int a = 20;
	int b = 100;
	printf("a : %d\n", a);
	printf("b : %d\n", b);
	swap (&a, &b);
	printf("After swap\n");
	printf("a : %d\n", a);
	printf("b : %d\n", b);
}


