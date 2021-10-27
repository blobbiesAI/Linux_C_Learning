//name=wxb;name   =wxb;name=  wxb;
//
#include <string.h>
#include <stdio.h>
#include "variable_cmd.h"

#define ARGVLEN 32
#define ENVMASIZE 10
extern int env_num;
extern env wxb_env[ENVMASIZE];

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



int run_set_cmd(env wxb_env[]){
	for(int i=0;i<env_num;i++){
		printf("%s=%s\n",wxb_env[i].name, wxb_env[i].val);
	}
	return 0;
}



int run_unset_cmd(char *argv[], env wxb_env[]){
	char *unset_env = argv[1];
	int unset_id;
	for(unset_id=0; unset_id<env_num; unset_id++){
		if(strcmp(wxb_env[unset_id].name, unset_env)==0)
			break;
	}
	for(int i = unset_id; i<env_num -1; i++){
		strcpy(wxb_env[i].name, wxb_env[i+1].name);
		strcpy(wxb_env[i].val,  wxb_env[i+1].val);
	}
	env_num--;
	return 0;
}

int run_equal_cmd(char *argv[], env wxb_env[]){
	//1.=
	char *new_argv[ARGVLEN] = {NULL};
	char *token = NULL;
	int i =0; int j =0;
	while(argv[i]){
		char *temp = argv[i];
		while( (token = strtok(temp,"="))!=NULL ){
			temp = NULL;
		//	printf("%s\n",token);
			new_argv[j++] = token; 
		}
		i++;
	}
	//2.add into env
	strcpy(wxb_env[env_num].name,new_argv[0]);
	strcpy(wxb_env[env_num].val,new_argv[1]);
	env_num++;
	return 0;
}


int run_variable_cmd(char *argv[], env wxb_env[]){
	if(strcmp(argv[0], "set")==0)
		run_set_cmd(wxb_env);
	else if(strcmp(argv[0], "unset")==0)
		run_unset_cmd(argv, wxb_env);	
	else{
		run_equal_cmd(argv, wxb_env);
	}
	return 0;
}


