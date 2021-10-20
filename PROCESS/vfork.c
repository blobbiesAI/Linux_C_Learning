#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	printf("before vfork\n");
	pid_t pnum = vfork();
	if(pnum==0){
		printf("vfork child process\n");
		exit(0);//important ; do not use return
	}
	else{
		printf("vfork parent process\n");
		return 0;
	}
	
}
