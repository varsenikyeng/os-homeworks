#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
        char path[128];
        char c;
        printf("Enter the existing file's  path: ");
        scanf("%s", path);
        int fd;
        ssize_t nr;
        fd = open(path, O_RDONLY);
	if(fd == -1){
		perror("open");
		return 1;
	}
	off_t size;
	size = lseek(fd, 0, SEEK_END);
	if(size == -1){
		perror("lseek");
		close(fd);
		return 1;
	}
	if(size == 0){
		if(write(1, "\n", 1) == -1){
			perror("write");
			return 1;
		}
		close(fd);
		return 0;
	}
	for(off_t i = size -1; i >= 0; i--){
		if(lseek(fd, i, SEEK_SET) == -1){
			perror("lseek");
			close(fd);
			return 1;
		}
		nr = read(fd, &c, 1);
		if(nr == -1){
			perror("read");
			return 1;
		}
		if(write(1, &c, 1) == -1){
                        perror("write");
                        return 1;
                }
	}
	
	if(write(1, "\n", 1) == -1) {
        	perror("write");
        	close(fd);
        	return 1;
	}
    	if(close(fd) == -1) {
		perror("close");
		return 1;
	}
}

