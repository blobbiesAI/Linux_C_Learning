#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
	printf("hello\n");
	int proid = fork();
	printf("id: %d\n", getpid());
	printf("world\n");
	printf("pid: %d\n", proid);
	exit(0);// exit current process;
	if(proid==0){
		printf("running child process\n");
	}
	else if(proid >0){
		printf("running parent process\n");
	}
	return 0;
}
