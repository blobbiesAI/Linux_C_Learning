//userspace--buff---> kernel space--buff--->hard disk
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 4096
//#define SYNC

int main(void){
	int fd;
#ifndef SYNC
	fd = open("hello.data", O_RDWR|O_CREAT);
#endif

#ifdef SYNC
	fd = open("hello.data", O_RDWR|O_CREAT|O_SYNC);//O_SYNC:sync()
#endif
	if(fd == -1){
		perror("open file wrong");
		return -1;
	}
	char *buffer = (char*)malloc(BUFFERSIZE*sizeof(char));
	strcpy(buffer,"hello world");
	write(fd,buffer,512);
	sync();
	return 0;
}
