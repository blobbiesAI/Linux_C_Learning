#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024



void dup_app(void){//operate on newfd is equal to opeantion on fd(the opened file!!!!)
	int fd = open("hello.data", O_RDWR|O_CREAT);
	int new_fd = dup(fd);
	char writebuff[20] = "hello world.";
	char *readbuff = (char*)malloc(BUFFERSIZE*sizeof(char));
	write(fd, writebuff, strlen(writebuff));
	lseek(fd,0,SEEK_SET);
	read(new_fd, readbuff, strlen(writebuff));
	close(new_fd);
	printf("%s\n",readbuff);
	free(readbuff);
	
	return;
}



/* implenmtation of shell > */
void dup2_app(void){
	int fd = open("dup2.data", O_RDWR|O_CREAT);
	int newfd = dup2(fd,1);//operate on 1 is equal on operate on the file(fd);
	printf("%d\n", newfd);

	char buff[20] = "hello wxb";
	write(newfd, buff, strlen(buff));
	close(fd);
	return;
}

/*implentation of shell | (like cat file | wc -l)*/
void pipe_dup2(void){
	int pipefd[2]={0};
	pipe(pipefd);
	
	int p_stat = vfork();
	if(p_stat == 0){
		
		char *pargs[3]={"cat","dup.c"};
		pargs[2]=NULL;

		dup2(pipefd[1],1);
		execvp(pargs[0],pargs);
		_exit(0);	
	}
	else if(p_stat > 0){
		wait(NULL);
		char *cargs[3]={"wc","-l"};
		cargs[2] = NULL;

		close(pipefd[1]);//????????why here, must have and must in parent process
		dup2(pipefd[0],0);		
		execvp(cargs[0],cargs);
		
	}
	return;
}


int main(void){
#if 0
	dup_app();
#endif
#if 0
	dup2_app();
#endif
	pipe_dup2();
	return 0;
}

