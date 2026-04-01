#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	printf("Enter the number of students: ");
	scanf("%d", &n);
	int *grades = (int *)malloc(n*sizeof(int));
	if (grades == NULL){
		printf("Malloc failed!");
		return 1;
	}
	printf("Enter the grades: ");
	int lowest;
	int highest;
	for(int i = 0; i < n; i++){
		scanf("%d", &grades[i]);
		if (i == 0)
			lowest = highest = grades[0];
		if (grades[i] >= highest){
			highest = grades[i];
		}
		if (grades[i] < lowest){
			lowest = grades[i];
		}
	}
	printf("Highest grade: %d", highest);
	printf("\nLowest grade: %d", lowest);
	free(grades);
	grades = NULL;
	return 0;

}
