#include <stdio.h>
#include <stdlib.h>

int main() {
        int *arr1, *arr2;
        arr1 = (int *)malloc(10 * sizeof(int));
        if (arr1 == NULL) {
        printf("Malloc failed!\n");
        }
        printf("Enter 10 integers: ");
        for(int i = 0; i < 10; i++){
		scanf("%d", &arr1[i]);
	}
	arr2 = (int *)realloc(arr1, 5 * sizeof(int));
	if (arr2 == NULL){
		printf("\nrealloc failed! original arr1 still valid");
		free(arr1);
		arr1 = NULL;
	}
        printf("Array after resizing: ");
	for(int i = 0; i < 5; i++){
		printf("%d ", arr2[i]);
	}
	printf("\n");
        free(arr2);
        arr2 = NULL;
        return 0;
}
