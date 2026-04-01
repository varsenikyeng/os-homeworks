#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
        const char *filename = "numbers.txt";
        int fd;
        ssize_t nw, nr;
        off_t offset;
	char buf[10];
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd == -1){
                perror("open");
		return 1;
        }
	for (int i = 1; i <= 10; i++){
		int len = snprintf(buf, sizeof(buf), "%d\n", i);
		if(len < 0){
			perror("formatting");
			return 1;
		}
		nw = write(fd, buf, len);
		if(nw <0 || nw != len){
			perror("write");
			return 1;
		}
	}
	if(close(fd) == -1){
		perror("close");
		return 1;
	}

	fd = open(filename, O_RDWR);
	if(fd == -1){
                perror("open");
                return 1;
        }
	int line = 1;
	char c;
	offset = 0;
	while((nr = read(fd, &c, 1)) == 1){
		if(nr == -1){
			perror("read");
		}
		offset++;
		if(c == '\n')
			line++;
		if (line == 4)
                        break;
	}
	if(line != 4){
		perror("Can't find 4th line");
		return 1;
	}

	if(lseek(fd, offset, SEEK_SET) == -1) {
        	perror("lseek");
        	close(fd);
        	return 1;
	}
	off_t start_4 = offset;
	off_t end_4 = start_4 + 2;
	off_t file_size = lseek(fd, 0, SEEK_END);
	size_t remainder_size = file_size - end_4;
	char remainder[remainder_size];
	if (lseek(fd, end_4, SEEK_SET) == -1) {
        	perror("lseek to remainder");
        	close(fd);
        	return 1;
   	}	
	nr = read(fd, remainder, sizeof(remainder));
	if(nr == -1){
		perror("read");
		return 1;
	}

	if (ftruncate(fd, start_4) == -1) {
        	perror("ftruncate");
        	close(fd);
        	return 1;
    	}
    
    	if (lseek(fd, start_4, SEEK_SET) == -1) {
        	perror("lseek before write");
        	close(fd);
        	return 1;
    	}
	const char *repl = "100\n";
	nw = write(fd, repl, strlen(repl));
	if(nw <0 || nw != strlen(repl)){
		perror("write");
		return 1;
	}
	nw = write(fd, remainder, nr);
	if (nw == -1) {
        	perror("write");
		return 1;
    	}
	if (lseek(fd, 0, SEEK_SET) == -1) {
		perror("");
		close(fd);
		return 1;
	}
	printf("Final file content:\n");
   	while ((nr = read(fd, buf, sizeof(buf))) > 0) {
        	write(1, buf, nr);
	}
	if(close(fd) == -1){
                perror("close");
                return 1;
        }
}

