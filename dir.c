#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv){
	DIR* dirptr = opendir(argv[1]);
	if(dirptr==NULL){
here:
		perror("ERROR:open a dir wrong");
		return -1;
	}

	struct dirent * dir;
	errno = 0;// man readdir; man errno
        while((dir = readdir(dirptr))!=NULL){
		if(errno) goto here; 
		printf("Inode:%ld ", dir->d_ino);
		printf("file type:%d ", dir->d_type);
		printf("file name:%s\n", dir->d_name);
	}
	int dirclose = closedir(dirptr);
	if(dirclose==-1){
		perror("ERROR:close a dir wrong");
		return -1;
	}

	return 0;
}

