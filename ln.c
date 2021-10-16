#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv){
	if(argc < 3 || argc > 4) goto here;
	int state;
	if(argc==3){
		state = link(argv[1], argv[2]);
	}
	else if((strcmp(argv[1], "-s"))==0){
		state = symlink(argv[2], argv[3]);
	}		
	
	
	if(state==-1){
here:
		perror("ERROR:link wrong");
		return -1;
	}
	return 0;
}
