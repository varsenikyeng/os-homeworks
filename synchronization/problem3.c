#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 8
int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

int P = 3;
int C = 3;
int K = 5;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

int buffer_count() {
    return (in_pos - out_pos + BUFFER_SIZE) % BUFFER_SIZE;
}

void* producer(void* arg){
	for(int i = 0; i < K; i++){
		int item = i;
		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);
		buffer[in_pos] = item;
		in_pos = (in_pos) + 1 % BUFFER_SIZE;

		printf("Produced %d | Buffer count = %d\n", item, buffer_count());

		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);
	}
	return NULL;
}

void* consumer(void* arg){
	int items_to_consume = (P*K)/ C;
	for (int i = 0; i < items_to_consume; i++){
		sem_wait(&full_slots);
		pthread_mutex_lock(&buffer_mutex);
		int item = buffer[out_pos];
		out_pos = (out_pos + 1) % BUFFER_SIZE;
		pthread_mutex_unlock(&buffer_mutex);

		printf("Consumed %d | Buffer count = %d\n", item, buffer_count());

		sem_post(&empty_slots);
	}
	return NULL;
}

int main(){
	
	pthread_t producers[P];
	pthread_t consumers[C];

	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);

	for(int i = 0; i < P; i++){
		if(pthread_create(&producers[i], NULL, producer, NULL) != 0){
			perror("Failed to create producer thread");
			return 1;
		}
	}

	for(int i = 0; i < C; i++){
                if(pthread_create(&consumers[i], NULL, consumer, NULL) != 0){
                        perror("Failed to create consumer thread");
                        return 1;
                }
        }

	for (int i = 0; i < P; i++)
        	pthread_join(producers[i], NULL);

	for (int i = 0; i < C; i++)
        	pthread_join(consumers[i], NULL);

	sem_destroy(&empty_slots);
	sem_destroy(&full_slots);
	pthread_mutex_destroy(&buffer_mutex);

	return 0;


}
