#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
	const char *filename = "data.txt";
	const char *buf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	int fd;
	ssize_t nr = 0;
	off_t size;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1) {
        	perror("open");
        	return 1;
	}
	nr = write(fd, buf, strlen(buf));
	if(nr == -1){
       		perror("write");
                return 1;
        }
	if(close(fd) == -1) {
        perror("close failed");
        return 1;
	}
	fd = open(filename, O_RDWR);
    	if(fd == -1) {
        	perror("open");
       		return 1;
	}
	size = lseek(fd, 0, SEEK_END);
	if(size == -1) {
        	perror("lseek failed");
		close(fd);
        	return 1;
	}
	printf("Current file size: %ld bytes\n", size);
	if(ftruncate(fd, 10) == -1) {
        	perror("ftruncate");
        	close(fd);
        	return 1;
	}
	size = lseek(fd, 0, SEEK_END);
        if(size == -1) {
                perror("lseek failed");
                close(fd);
                return 1;
        }
	printf("After truncate file size: %ld bytes\n", size);
	
	if(lseek(fd, 0, SEEK_SET) == -1){
                perror("lseek failed");
                close(fd);
                return 1;
        }

	char buf2[100];
	nr = read(fd, buf2, sizeof(buf2)-1);
	if (nr == -1) {
		perror("read");
		return 1;
	}
	buf2[nr] = '\0';
	printf("Remaining content: %s\n", buf2);
	if (close(fd) == -1) {
		perror("close");
		return 1;
	}
	
}

