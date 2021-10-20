#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 4096

//
// child process write--->parent process read;
//
//
int main(void){
	printf("begin run parent process\n");
	int pipefd[2]={0};
	pipe(pipefd);

	pid_t state = fork();
	if(state==0){
		printf("begin run child process and hung up parent process\n");
		char writebuff[20] = "hello world";
		ssize_t w_state = write(pipefd[1], writebuff, BUFFERSIZE);
		close(pipefd[1]);

		if(w_state==-1){
			perror("write");
			exit(-1);
		}
		printf("exit child process\n");
		exit(0);
	}
	else if(state >0){
		wait(NULL);
		printf("wake parent process\n");
		char *readbuff = (char*)malloc(BUFFERSIZE*sizeof(char));
		ssize_t r_state = read(pipefd[0], readbuff, BUFFERSIZE);
		close(pipefd[0]);

		if(r_state==-1){
			perror("read");
			exit(-1);
		}
		printf("%s\n",readbuff);
		free(readbuff);
		printf("exit parent process\n");
	}
	return 0;
}
