#include <stdio.h>
#include <stdlib.h>

int main() {
        int *arr;
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        arr = (int *)calloc(n, sizeof(int));
        if (arr == NULL) {
        printf("Calloc failed!\n");
        }
	printf("Array after calloc : ");
	for(int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
        printf("\nEnter %d integers: ", n);
        int sum = 0;
        for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        sum += arr[i];
        }
	printf("\nUpdated array : ");
	for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
        }
	double avg = (double)sum/n;
        printf("\nAverage of the array : %lf\n", avg);
        free(arr);
        arr = NULL;
        return 0;
}
