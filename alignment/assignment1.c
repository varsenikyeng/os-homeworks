#include <stdio.h>

int main(){
	int i;
	char c;
	double d;
	short s;
	printf("Size of int: %ld \n", sizeof(int));
	printf("Size of char: %ld \n", sizeof(char));
	printf("Size of double: %ld \n", sizeof(double));
	printf("Size of short: %ld \n", sizeof(short));
	printf("int address : %p \n", &i);
	printf("char address : %p \n", &c);
	printf("double address : %p \n", &d);
	printf("short address : %p \n", &s);


}
