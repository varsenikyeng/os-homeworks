#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
	char src_path[256];
	char dest_path[256];
	char buf[BUFSIZ];
	printf("Enter the source file's  path: ");
	scanf("%s", src_path);
	printf("Enter the destination file's path: ");
	scanf("%s", dest_path);
	int src, dest;
	ssize_t nr, nw;
	int total = 0;

	src = open(src_path, O_RDONLY);
	if(src == -1){
		perror("opening src");
		return 1;
	}

	dest = open(dest_path,O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(dest == -1){
		perror("opening dest");
		close(src);
		return 1;
	}
	while((nr = read(src, buf, BUFSIZ)) != 0){
		if(nr == -1){
			perror("read");
			break;
		}
		nw = write(dest, buf, nr);
		if(nw == -1){
			perror("write");
			break;
		}
		total += nw;
	}
	printf("Total number of bytes copied : %d\n", total);
	if(close(src) == -1){
		perror("close");
		return 1;
	}
	if(close(dest) == -1){
		perror("close");
		return 1;
	}
}
