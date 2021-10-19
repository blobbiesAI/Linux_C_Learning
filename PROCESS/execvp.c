#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define FORK_CHILD_PROCESS

int main(int argc, char **argv){
	printf("before execvp......\n");
#ifdef FORK_CHILD_PROCESS
	int pid = fork();
	if(pid==-1){
		perror("ERROR:create child process wrong");
		return -1;
	}
	printf("pid = %d\n", pid);
#endif
#if 0
	char *args[5];
	args[0] = "ls";
	args[1] = "-l";
	args[2] = "-a";
	args[3] = NULL;
	int state = execvp(args[0], args);
#endif	
	if(pid==0){
		int state = execvp(argv[1], argv+1);
		if(state==-1){
			perror("ERROR:execvp wrong");
			return -1;
		}
		exit(0);
	}
	printf("after execvp......\n");

	return 0;
}
