#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	int state;
	if((state = rmdir(argv[1]))==-1){
		perror("ERROR:remove dir wrong");
		return -1;
	}
	return 0;
}
