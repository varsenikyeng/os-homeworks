#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10
sem_t semA, semB, semC;
pthread_mutex_t print_mutex;

void* thread_a(void* arg) {
	for (int i = 0; i < N; i++) {
		sem_wait(&semA);
		pthread_mutex_lock(&print_mutex);
		printf("A %d ", i);
		pthread_mutex_unlock(&print_mutex);
		sem_post(&semB);
    	}
	return NULL;
}

void* thread_b(void* arg) {
        for (int i = 0; i < N; i++) {
                sem_wait(&semB);
                pthread_mutex_lock(&print_mutex);
                printf("B %d ", i);
                pthread_mutex_unlock(&print_mutex);
                sem_post(&semC);
        }
        return NULL;
}

void* thread_c(void* arg) {
        for (int i = 0; i < N; i++) {
                sem_wait(&semC);
                pthread_mutex_lock(&print_mutex);
                printf("C %d ", i);
                pthread_mutex_unlock(&print_mutex);
                sem_post(&semA);
        }
        return NULL;
}

int main(){
	
	pthread_t thread_A, thread_B, thread_C;

	sem_init(&semA, 0, 1);
	sem_init(&semB, 0, 0);
	sem_init(&semC, 0, 0);
	pthread_mutex_init(&print_mutex, NULL);
	pthread_create(&thread_A, NULL, thread_a, NULL);
	pthread_create(&thread_B, NULL, thread_b, NULL);
	pthread_create(&thread_C, NULL, thread_c, NULL);

	pthread_join(thread_A, NULL);
	pthread_join(thread_B, NULL);
	pthread_join(thread_C, NULL);

	sem_destroy(&semA);
	sem_destroy(&semB);
	sem_destroy(&semC);
	pthread_mutex_destroy(&print_mutex);

	return 0;


}
