#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int C_FLAG;


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
		if(dir->d_name[0]=='.') continue;
	        if(C_FLAG==1 && strstr(dir->d_name,".c")==NULL) continue;	
		//printf("inode:%ld ", dir->d_ino);
		//printf("file type:%d ", dir->d_type);
		printf("%s  ", dir->d_name);
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
	char *mode;
	C_FLAG = 0;

	if(argc==1){//default current dir
		dirptr = opendir(".");
		printfdir(dirptr);
	}
	else{
		for(int i=1; i<argc; i++){
			if(strcmp(argv[i],"-c")==0){//two string compare
				C_FLAG = 1;
				if(argc==2){
					dirptr = opendir(".");
					printfdir(dirptr);

				}
				continue;
			}
				
			dirptr = opendir(argv[i]);
			printfdir(dirptr);
		}
	}

	return 0;
}

