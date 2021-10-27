#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "buildin_cmd.h"
#include "variable_cmd_v2.h"

int buildin_cd_cmd(char *args[]){
	if(args[1]==NULL) goto here;
	int stat = chdir(args[1]);
	if(stat ==-1){
		perror("chdir");
		return -1;
	}
here:
	return 0;
}



int build_exit_cmd(char *args[], char **minishell_var){
	pid_t pid = getpid();
	env_free_cmd(minishell_var);
	kill(pid, SIGHUP);
	return 0;
}

int read_analyse_buildin_cmd(char *args[], char **minishell_var){
	if(strcmp(args[0], "cd")==0)
		buildin_cd_cmd(args);
	else if(strcmp(args[0],"exit")==0)
		build_exit_cmd(args, minishell_var);
	else
		return -1;
	return 0;
}
