#include <stdio.h>

struct DataHolder1 {
        char a;
        int b;
        double c;
};

#pragma pack(1)
struct DataHolder2 {
	char a;
	int b;
	double c;
};

#pragma pack(4)
struct DataHolder3 {
        char a;
        int b;
        double c;
};

int main(){
	struct DataHolder1 example1;
        printf("Size of DataHolder : %lu bytes \n", sizeof(example1));
        printf("Char a : %p \n", &example1.a);
        printf("Int b : %p \n", &example1.b);
        printf("Double c : %p \n", &example1.c);
	printf("\n");
	printf("Using pragma pack(1) ... \n");
	struct DataHolder2 example2;
        printf("Size of DataHolder : %lu bytes \n", sizeof(example2));
        printf("Char a : %p \n", &example2.a);
        printf("Int b : %p \n", &example2.b);
        printf("Double c : %p \n", &example2.c);
	printf("\n");
	printf("Using pragma pack(4) ... \n");
	struct DataHolder3 example3;
        printf("Size of DataHolder : %lu bytes \n", sizeof(example3));
        printf("Char a : %p \n", &example3.a);
        printf("Int b : %p \n", &example3.b);
        printf("Double c : %p \n", &example3.c);

}
