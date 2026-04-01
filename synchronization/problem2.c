#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
long long balance = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spinlock;

int is_mutex = 1;
int short_cs = 1;
int N = 5;
long long M = 100000;

void* deposit(void* arg){
	for(long long i = 0; i < M; i++){
		if(is_mutex){
			pthread_mutex_lock(&mutex);
		}
		else{
			pthread_spin_lock(&spinlock);
		}

		if(!short_cs){
			usleep(100);
		}
		balance++;
		if(is_mutex){
			pthread_mutex_unlock(&mutex);
		}
		else{
			pthread_spin_unlock(&spinlock);
		}
	}
	return NULL;
}

void* withdraw(void* arg){
        for(long long i = 0; i < M; i++){
                if(is_mutex){
                        pthread_mutex_lock(&mutex);
                }
                else{
                        pthread_spin_lock(&spinlock);
                }

                if(!short_cs){
                        usleep(100);
                }
                balance--;
                if(is_mutex){
                        pthread_mutex_unlock(&mutex);
                }
                else{
                        pthread_spin_unlock(&spinlock);
                }
        }
        return NULL;
}

int main(int argc, char *argv[]){
	if (argc != 3){
		printf("Usage: ./bank mutex|spin short|long\n");
		return 1;
	}

	if (strcmp(argv[1], "mutex") == 0){
		is_mutex = 1;
	}
	else if (strcmp(argv[1], "spin") == 0){
		is_mutex = 0;
	}
	else{
		printf("Wrong lock \n");
		return 1;
	}

	if (strcmp(argv[2], "short") == 0){
                short_cs = 1;
        }
        else if (strcmp(argv[2], "long") == 0){
                short_cs = 0;
        }
        else{
		printf("Wrong cs type\n");
                return 1;
        }

	pthread_mutex_init(&mutex, NULL);
	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

	pthread_t threads[N + N];

	for (int i = 0; i < N; i++){
		if(pthread_create(&threads[i], NULL, deposit, NULL) != 0){
			perror("Failed to create thread");
		}
	}

	for (int i = 0; i < N; i++){
                if(pthread_create(&threads[N + i], NULL, withdraw, NULL) != 0){
                        perror("Failed to create thread");
                }
        }

	for (int i = 0; i < N + N; i++){
                if(pthread_join(threads[i], NULL) != 0){
			perror("Failed to join thread");
                }
        }

	printf("Final balance = %lld\n", balance);

	pthread_mutex_destroy(&mutex);
	pthread_spin_destroy(&spinlock);

	return 0;



	
}
