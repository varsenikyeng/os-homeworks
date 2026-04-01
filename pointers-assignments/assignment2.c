#include <stdio.h>

int main(void)
{
	int arr[5] = {0, 1, 2, 3, 4};
	int *ptr = arr;
	for (int i = 0; i<5; i++){
		printf("%d ", *(ptr+i));
	}
	printf("\n");
	*(ptr + 1) = 10;
	*(ptr + 3) = 20;
	for(int i =0; i<5; i++)
	{
		printf("%d ",*(ptr + i));
	}
	printf("\n");

	for (int i = 0; i < 5; i++)
	{
       		printf("%d ", arr[i]);
	}

}


