//name=wxb;name   =wxb;name=  wxb;
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "variable_cmd.h"
#include "variable_cmd_v2.h"
//extern int env_num;
//extern char **environ;
//extern char **minishell_var;

int is_variable_cmd(char *argv[]){
	int i = 0;
	while(argv[i]){
		if(strstr(argv[i],"="))
			return 1;
		if(strcmp(argv[i],"set")==0)
			return 1;
		if(strcmp(argv[i],"unset")==0)
			return 1;
		i++;
	}
	return 0;
}


int env_init_cmd(char **minishell_var){
	char **p = environ;
	unsigned int slen;
	int i = 0;
	while(p[i]!=NULL){
		slen = strlen(p[i]);
		minishell_var[i] = (char*)malloc(sizeof(char)*(slen+1));//+1?
		strcpy(minishell_var[i],p[i]);
		i++;
	}
	env_num = i;
	return 0;
}


int env_free_cmd(char **minishell_var){
	for(int i = 0; i< env_num; i++)
		free(minishell_var[i]);
	return 0;
}

int run_set_cmd(char **minishell_var){
	for(int i=0;i<env_num;i++){
		printf("%s\n",minishell_var[i]);
	}
	return 0;
}



int run_unset_cmd(char *argv[], char **minishell_var){
	char *unset_env = argv[1];
	int unset_id;
	for(unset_id=0; unset_id<env_num; unset_id++){
		if(strncmp(minishell_var[unset_id], unset_env, strlen(unset_env))==0){
			free(minishell_var[unset_id]);
			break;
		}
	}
	for(int i = unset_id; i<env_num -1; i++){
		minishell_var[i] = minishell_var[i+1];
	}
	env_num--;
	return 0;
}

int run_equal_cmd(char *argv[], char **minishell_var){
	int i = 0;
	char *new_env = argv[i];
	while(argv[i+1]){
		new_env = strcat(new_env, argv[i+1]);
		i++;
	}

	minishell_var[env_num] = (char*)malloc(strlen(new_env)+1);
	
	strcpy(minishell_var[env_num], new_env);
	env_num++;
	return 0;
}


int run_variable_cmd(char *argv[], char **minishell_var){
	if(strcmp(argv[0], "set")==0)
		run_set_cmd(minishell_var);
	else if(strcmp(argv[0], "unset")==0)
		run_unset_cmd(argv, minishell_var);	
	else{
		run_equal_cmd(argv, minishell_var);
	}
	return 0;
}


