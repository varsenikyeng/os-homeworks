#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N = 4;
long long M = 1000000;
long long counter = 0;

pthread_spinlock_t spinlock;

void* incrementor(void* arg){
	for (long long i = 0; i < M; i++){
		pthread_spin_lock(&spinlock);
		counter++;
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

int main(){
	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

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

	pthread_spin_destroy(&spinlock);

	return 0;
}

