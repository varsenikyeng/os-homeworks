#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 5
int arr[] = {1, 2, 3, 4, 5};
void* calculate_square(void* arg){
	int num = *(int*)arg;
	printf("Sqaure of %d is %d \n", num, num*num);
	return NULL;
}
int main(){
	pthread_t threads[SIZE];
	for(int i =0; i< SIZE; i++){
		if(pthread_create(&threads[i], NULL, calculate_square, &arr[i])!=0){
			perror("Failed to create thread");
			return 1;
		}
	}

	for(int i = 0; i < SIZE; i++){
		if (pthread_join(threads[i], NULL) != 0) {
        		perror("Failed to join thread");
        		return 1;
		}
	}

	printf("All threads finished execution.");
        return 0;

}
