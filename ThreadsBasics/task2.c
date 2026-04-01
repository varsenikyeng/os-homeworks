#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 4
int arr[] = {1, 2, 3, 4};

void* sum_half(void* arg) {
    int start = *(int*)arg;
    int end = start + SIZE / 2;
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }

    printf("Thread of TID: %lu sum = %d\n", pthread_self(), sum);
    return NULL;
}

int main(){
	pthread_t thread1;
	pthread_t thread2;
	int start1 = 0;
	int start2 = SIZE / 2;
	if (pthread_create(&thread1, NULL, sum_half, &start1) !=0){
		perror("Failed to create thread 1");
                return 1;
        }

	if (pthread_create(&thread2, NULL, sum_half, &start2) != 0) {
        	perror("Failed to create thread 2");
        	return 1;
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("All threads finished execution.");
	return 0;
		
}
