#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 1024

int main(void){
	mkfifo("my_fifo.data", 0666);
	int fd = open("my_fifo.data", O_RDWR);
	int p_stat = vfork();
	if(p_stat==0){
		printf("begin child process\n");
		char writebuff[BUFFERSIZE] = "hello world";
		write(fd, writebuff, BUFFERSIZE);
		_exit(0);
	}
	else if(p_stat > 0){
		printf("begin parent process\n");
		char *readbuff = (char*)malloc(BUFFERSIZE*sizeof(char));
		read(fd, readbuff, BUFFERSIZE);
		printf("%s\n", readbuff);
		free(readbuff);
		close(fd);
	}
	return 0;
}
