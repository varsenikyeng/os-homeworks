#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
        const char *filename = "log.txt";
	int fd;
	ssize_t nr, nw;
	char input[BUFSIZ];
	char output[BUFSIZ + 10];
	off_t offset;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if(fd == -1) {
		perror("open");
		return 1;
	}
	printf("Enter something : \n");
	nr = read(0, input, BUFSIZ -1);
	if(nr == -1){
		perror("read");
		return 1;
	}
	input[nr] = '\0';

	int pid = getpid();
	int written = snprintf(output, sizeof(output), "PID= %d: %s\n", pid, input);

	if(written <0){
		perror("Formatting");
		close(fd);
		return 1;
	}
	nw = write(fd, output, written);
	if (nw == -1){
		perror("write");
		return 1;
	}
	offset = lseek(fd, 0, SEEK_CUR);
	if(offset == -1){
		perror("lseek");
		close(fd);
		return 1;
	}
	printf("New file offset: %ld\n", offset);
	if (close(fd) == -1){
		perror("close");
		return 1;
	}


/* 
 * Explanation:
 * We used O_APPEND which ensures all writes go to the end of the file even if multiple
 * processes are writing. SEEK_CUR returns the current file 
 * offset in this process, which grows with each write as in the end of writing process it's in the end.
*/


}
