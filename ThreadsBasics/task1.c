#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void* print_message(void* arg){
	int thread_num = *((int *)arg);
	printf("Thread %d is running. ID: %lu \n", thread_num, pthread_self());
	return NULL;
}
int main(){
	pthread_t thread1, thread2, thread3;
	int thread_id_1 = 1;
	int thread_id_2 = 2;
	int thread_id_3 = 3;
	if (pthread_create(&thread1, NULL, print_message, &thread_id_1) !=0){
		perror("Failed to create thread 1");
		return 1;
	}
	if (pthread_create(&thread2, NULL, print_message, &thread_id_2)!=0){
                perror("Failed to create thread 2");
                return 1;
        }
	if (pthread_create(&thread3, NULL, print_message,  &thread_id_3)!=0){
                perror("Failed to create thread 3");
                return 1;
        }
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	printf("All threads finished execution.");
	return 0;
}
