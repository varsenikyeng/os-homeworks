#include <stdio.h>

struct DataHolder {
	double c;
	int b;
	char a;
};
int main(){
	struct DataHolder example;
	printf("Size of DataHolder : %lu bytes \n", sizeof(example));
	printf("Char a : %p \n", &example.a);
	printf("Int b : %p \n", &example.b);
	printf("Double c : %p \n", &example.c);

}
