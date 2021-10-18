#include <unistd.h>
#include <stdio.h>

//#define FORK_CHILD_PROCESS

int main(int argc, char **argv){
	printf("before execvp......\n");
#ifdef FORK_CHILD_PROCESS
	int pid = fork();
	printf("pid = %d\n", pid);
#endif
	
	int state = execvp(argv[1], );

	printf("after execvp......\n");

	return 0;
}
