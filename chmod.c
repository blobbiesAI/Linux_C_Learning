#include <sys/stat.h>
#include <stdio.h>
#include "strto.h"
int main(int argc, char **argv){
		
	int return_fd = chmod(argv[2], strtoi(argv[1],NULL,8));
	if(return_fd==-1){
		perror("ERROR:change mode failure");
		return -1;
	}
	return 0;
}
