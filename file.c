#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
	int fd = open("hello.txt", O_RDWR|O_CREAT);
	if(fd==-1){
		printf("ERROR:failure happened when open a normal file;\n");
		return -1;
	}
	
	char *buff = "hello world.\n";
	write(fd,buff,14);
	fsync(fd);

	char* rdbuf = (char*)malloc(20);
	memset(rdbuf,0,20);
	lseek(fd,0,SEEK_SET);
	read(fd,rdbuf,14);
	printf("%s",rdbuf);

	free(rdbuf);
	close(fd);
	return 0;
}      
