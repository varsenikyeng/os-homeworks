#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_num(void* arg){
	for(int i = 1; i<= 5; i++){
		printf("Thread (TID : %lu) printing: %d \n", pthread_self(), i);
	}
	return NULL;
}

int main(){
        pthread_t thread1, thread2, thread3;
	 if (pthread_create(&thread1, NULL, print_num, NULL) !=0){
                perror("Failed to create thread 1");
                return 1;
        }
        if (pthread_create(&thread2, NULL, print_num, NULL)!=0){
                perror("Failed to create thread 2");
                return 1;
        }
        if (pthread_create(&thread3, NULL, print_num,  NULL)!=0){
                perror("Failed to create thread 3");
                return 1;
        }
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        pthread_join(thread3, NULL);

	printf("All threads finished execution.");
        return 0;

        
}
