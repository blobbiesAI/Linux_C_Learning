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


int buildin_export_cmd(char *argv[]){
	char *new_argv[2]={NULL};
	char *token = NULL;
        int i = 1; int j =0;

        while(argv[i]){
        	char *temp = argv[i];
                while( (token = strtok(temp,"="))!=NULL ){
                	temp = NULL;
                        new_argv[j++] = token;
                }
                i++;
        }
	
	setenv(new_argv[0], new_argv[1], 0);
	//env_num++;
	return 0;
}


int read_analyse_buildin_cmd(char *args[], char **minishell_var){
	if(strcmp(args[0], "cd")==0)
		buildin_cd_cmd(args);
	else if(strcmp(args[0],"exit")==0)
		build_exit_cmd(args, minishell_var);
	else if(strcmp(args[0],"export")==0){
		if(args[1]==NULL) return 0;
		buildin_export_cmd(args);
	}
	else
		return -1;
	return 0;
}
