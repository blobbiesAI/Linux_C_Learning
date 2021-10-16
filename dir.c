#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int printfdir(DIR* dirptr){
	if(dirptr==NULL){
here:
		perror("error:open a dir wrong");
		return -1;
	}

	struct dirent * dir;
	errno = 0;// man readdir; man errno
       	while((dir = readdir(dirptr))!=NULL){
		if(errno) goto here; 
		printf("inode:%ld ", dir->d_ino);
		printf("file type:%d ", dir->d_type);
		printf("file name:%s\n", dir->d_name);
	}
	int dirclose = closedir(dirptr);
	if(dirclose==-1){
		perror("error:close a dir wrong");
		return -1;
	}
	printf("\n");
	
}

int main(int argc, char **argv){
	DIR* dirptr;

	if(argc==1){//default current dir
		dirptr = opendir(".");
		printfdir(dirptr);
	}
	else{
		for(int i=1; i<argc; i++){
			dirptr = opendir(argv[i]);
			printfdir(dirptr);
		}
	}

	return 0;
}

