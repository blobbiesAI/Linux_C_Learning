#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


//fork vfork wait
int main(void){
	printf("before fork\n");
	int state = fork();
	if(state==0){
		printf("running child process\n");
		exit(0);
	}	
	else if(state>0){
		printf("wait\n");
		wait(NULL);
		printf("running parent process\n");
	}
	return 0;
}
