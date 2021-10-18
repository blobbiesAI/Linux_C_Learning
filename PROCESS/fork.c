#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
	printf("hello\n");
	int proid = fork();
	printf("world\n");
	printf("pid: %d\n", proid);
	if(proid==0){
		printf("running child process\n");
	}
	else if(proid >0){
		printf("running parent process\n");
	}
	return 0;
}
