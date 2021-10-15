#include <stdio.h>
#include <stdlib.h>
#define BUFFERSIZE 4096

int main(int argc, char **argv){
	FILE * srcfd = fopen(argv[1], "r");
	if(srcfd==NULL){
		printf("ERROR:failure happend when open a normal file.\n");
	}
	FILE * objfd = fopen(argv[2], "w+");
	if(objfd==NULL){
		printf("ERROR:failure happend when open a normal file.\n");
	}

	char *buff = (char*)malloc(4096*sizeof(char));
	while(fread(buff,sizeof(char),BUFFERSIZE,srcfd)){
		fwrite(buff,sizeof(char),BUFFERSIZE,objfd);
	}

	free(buff);
	return 0;
}
