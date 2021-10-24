#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "buildin_cmd.h"

int buildin_cd_cmd(char *args[]){
	int stat = chdir(args[1]);
	if(stat ==-1){
		perror("chdir");
		return -1;
	}
	return 0;
}



int build_exit_cmd(char *args[]){
	return 0;
}

int read_analyse_buildin_cmd(char *args[]){
	if(strcmp(args[0], "cd")==0)
		buildin_cd_cmd(args);
	else if(strcmp(args[0],"exit")==0)
		build_exit_cmd(args);
	else
		return -1;
	return 0;
}
