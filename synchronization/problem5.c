#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K 3
#define N 10
sem_t printers;
pthread_mutex_t count_mutex;
int count_threads = 0;

void* print_job(void* arg){
	int id = *(int*)arg;
	sem_wait(&printers);

	pthread_mutex_lock(&count_mutex);
	count_threads++;
	printf("Thread %d is printing...\n", id);
	printf("Active printers = %d\n", count_threads);
	pthread_mutex_unlock(&count_mutex);

	usleep(200000);

	pthread_mutex_lock(&count_mutex);
	count_threads--;
	printf("Active printers = %d\n", count_threads);
	pthread_mutex_unlock(&count_mutex);
	
	sem_post(&printers);
	
	return NULL;
}

int main(){

	pthread_t threads[N];
	int thread_id[N];

	sem_init(&printers, 0, K);
	pthread_mutex_init(&count_mutex, NULL);

	for (int i = 0; i < N; i++){
		thread_id[i] = i;
		if (pthread_create(&threads[i], NULL, print_job, &thread_id[i]) != 0) {
			perror("Failed to create thread");
			return 1;
		}
	}

	for (int i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}

	sem_destroy(&printers);
       	pthread_mutex_destroy(&count_mutex);
	
	return 0;	
}
