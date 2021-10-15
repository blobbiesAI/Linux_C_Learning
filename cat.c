#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFERSIZE 4096
int main(int argc, char** argv){
	for(int i = 1; i < argc; i++){
		int fd = open(argv[i], O_RDONLY);
		if(fd==-1){
			perror("ERROR:failure happened when open a normal file");
		}

		char *buff = (char*)malloc(BUFFERSIZE*sizeof(char));
		unsigned int count;
		while((count = read(fd, buff, BUFFERSIZE)) > 0){
			write(1, buff, count);//1 is screen,0 is keyboard
		}
		printf("\n");
		free(buff);
		close(fd);
	}
	return 0;
}
