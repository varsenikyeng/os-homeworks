#include <stdio.h>
#include <stdlib.h>

int main(){
	char **strings;
	strings = (char **)malloc(3 * sizeof(char*));
	if (strings == NULL) {
        	printf("Malloc failed!\n");
    	}
	for(int i = 0; i < 3; i++){
		strings[i] = (char *)malloc(50*sizeof(char));
		if (strings[i] == NULL) {
            		printf("Malloc failed for string %d\n", i);
			return 1;
        	}
	}
	printf("Enter 3 strings : ");
	for(int i = 0; i < 3; i++){
		scanf("%s", strings[i]);
	}
	for(int i = 0; i < 3; i++){
                printf("%s ", strings[i]);
        }
	char **strings_new = (char **)realloc(strings, 5*sizeof(char*));
	if (strings_new == NULL) {
        	printf("Realloc failed!\n");
        	for (int i = 0; i < 3; i++) 
			free(strings[i]);
        	free(strings);
        	return 1;
    	}
	for (int i = 3; i < 5; i++) {
        	strings_new[i] = (char *)malloc(50 * sizeof(char));
        	if (strings_new[i] == NULL) {
            		printf("Malloc failed for string %d\n", i);
            		return 1;
       		}
    	}
	printf("\nEnter 2 more strings : ");
	scanf("%s", strings_new[3]);
	scanf("%s", strings_new[4]);
	printf("\nAll strings : ");
	for(int i = 0; i< 5; i++){
		printf("%s ", strings_new[i]);
	}
	free(strings_new);
	strings_new = NULL;
	return 0;
}
