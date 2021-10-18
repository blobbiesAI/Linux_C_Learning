#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <stdlib.h>


//bug*******
//TODO
void resursive_search_files(char * pathname, char **filename){
	DIR* dirptr = opendir(pathname);
	struct dirent *direntptr;
	static int elem = 0;
	errno = 0;
	//char ** ptr = filename;
        while((direntptr=readdir(dirptr)) != NULL){
		if(errno){perror("error"); return;}
		if(direntptr->d_name[0]=='.') continue;
		if(direntptr->d_type == DT_DIR){
		
			pathname = strcat(pathname,"/");
			printf("%s %s\n", pathname, direntptr->d_name);
			resursive_search_files(strcat(pathname, direntptr->d_name), filename);
			pathname[strlen(pathname) - strlen(direntptr->d_name) - 1]='\0';
			//printf("%s\n", pathname);	
		}
		else if(direntptr->d_type==DT_REG){
			filename[elem] = direntptr->d_name;
			//printf("%d ", elem);
			elem++;
			//printf("%ld--", telldir(dirptr));
		}
	}
	closedir(dirptr);
	return;
}


int filter_postfix(char **filename, char *postfix){
	int count=0;
	for(int i=0; i<100000;i++){
		if(filename[i]==NULL) break;
		if(strstr(filename[i], postfix)) count++;
	}
	return count;
}



int main(int argc, char **argv){
	char *filename[100000]={NULL};
	resursive_search_files(argv[1], filename);
	for(int i = 0; i<30000; i++){
		if(filename[i]==NULL) break;
		printf("%s\n", filename[i]);
	}
	printf("C file number is: %d\n",filter_postfix(filename, ".c"));
	printf("Header file number is: %d\n",filter_postfix(filename, ".h"));
	printf("Assembly file number is: %d\n",filter_postfix(filename, ".S"));

	return 0;
}
