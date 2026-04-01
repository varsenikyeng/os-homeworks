#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
        const char *filename = "sparse.bin";
	int fd;
        ssize_t nw;
        off_t offset;
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1){
		perror("open");
		return 1;
	}

	const char *buf = "START";
	nw = write(fd, buf, strlen(buf));
	if(nw == -1){
		perror("write");
		return 1;
	}

	offset = lseek(fd, 1024*1024, SEEK_CUR);
	if(offset == -1){
		perror("lseek");
		close(fd);
		return 1;
	}

	const char *buf2 = "END";
	nw = write(fd, buf2, strlen(buf2));
	if(nw == -1){
		perror("write");
		return 1;
	}

	if(close(fd) == -1){
		perror("close");
		return 1;
	}

	fd = open(filename, O_RDONLY);
	if(fd == -1){
		perror("reopen");
		return 1;
	}
	offset = lseek(fd, 0, SEEK_END);
	if(offset == -1){
                perror("lseek");
                close(fd);
                return 1;
        }
	printf("APparent file size : %ld bytes \n", offset);
	if(close(fd) == -1){
		perror("close");
		return 1;
	}

}
/*
     *Explanation:
     * The file appears to be about 1,048,584 bytes.
     * However,whem we check disk usage with du, its 8.0k,  much smaller because the 1 MiB gap contains no actual data blocks.
     * The filesystem marks that region as "unallocated"(takes no real disk space).
*/
