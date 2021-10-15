#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 4096
int main(int argc, char **argv){
	int srcfd = open(argv[1],O_RDONLY);
	if(srcfd==-1){
		perror("ERROR:failure happened when open a normal file.");
		return -1;
	}
	int objfd = open(argv[2],O_WRONLY|O_CREAT);
	if(objfd==-1){
		perror("ERROR:failure happened when open a normal file.");
		return -1;
	}	

	int read_count;
	char* buff = (char*)malloc(BUFFERSIZE);
	while((read_count=read(srcfd,buff,BUFFERSIZE))>0){
		write(objfd,buff,read_count);
	}
	if (read_count < 0){
		perror("ERROR:read file wrong");
		return -1;
	}
	free(buff);
	close(srcfd);
	close(objfd);
	return 0;
}      
