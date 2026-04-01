#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N = 4;
long long M = 1000000;
long long counter = 0;

pthread_mutex_t mutex;

void* incrementor(void* arg){
	for (long long i = 0; i < M; i++){
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(){
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[N];

	for(int i = 0; i < N; i++){
		if(pthread_create(&threads[i], NULL, incrementor, NULL)!= 0){
			perror("Failed to create thread");
			return 1;
		}
	}

	for(int i = 0; i < N; i++){
		if(pthread_join(threads[i], NULL) != 0){
			perror("Failed to join thread");
			return 1;
		}
	}

	printf("Expected value : %lld", N*M);
	printf("\nActual value : %lld\n", counter);

	pthread_mutex_destroy(&mutex);

	return 0;
}
