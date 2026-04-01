#include <stdio.h>
#include <stdlib.h>

int main() {
	int *arr;
	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL) {
        printf("Malloc failed!\n");
	}

	printf("Enter %d integers: ", n);
       	int sum = 0;
	for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        sum += arr[i];
	}
	printf("Sum of the array: %d\n", sum);
	free(arr);
	arr = NULL;
	return 0;
}

