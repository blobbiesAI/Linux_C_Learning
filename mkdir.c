#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
	int state;
	if((state = mkdir(argv[1], 0777))==-1){
		perror("ERROR:make dir wrong");
		return -1;
	}
	return 0;
}
