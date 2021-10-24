#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <signal.h>
#include "buildin_cmd.h"
#define ARGVLEN 32
#define STRLEN 128

int is_background=0;

void read_analyse_cmd(char *str, char *args[]){
	//char str[STRLEN] = {0};  //ls\0-a\0-l\0
	int i = 0;int j = 0;
	char *p = str;
	char c = 0;
	while(1){	
			
		c = getchar();   //loop stop here, to wait for stdin input
		if(c==' ' || c=='\t' || c=='\n'){
			if(i==0){
				if(c=='\n') 
					break;  //exit when we have kong ge after last variable
				continue;
			}
			else{
				p[i++]='\0';
				args[j++] = p;
				p +=i;
			       	i=0;
				if(c=='\n')
					break; //exit when we donot have kong ge after last variable	
			}
		}
		else{
			if(c=='&'){
				is_background = 1;//creat a flag
				continue;  //do not put & in args, it just a biaozhi
			}
			p[i++] = c;
		}
			
	}
	return;	
}


void run_cmd(char *argv[]){
	int p_stat = fork();
	if(p_stat == 0){
		signal(SIGINT,SIG_DFL);	
		if(execvp(argv[0],argv) == -1){
			perror("execvp");
			_exit(-1);
		}
		_exit(0);
			
	}
	else if(p_stat > 0 && is_background==0){
		signal(SIGINT,SIG_IGN);
		signal(SIGCHLD,SIG_DFL);
		wait(NULL);
	}
	else if(p_stat >0 && is_background==1){//enable background running
		signal(SIGCHLD,SIG_IGN);
		signal(SIGINT,SIG_IGN);
		is_background=0;
	}
	else{
		perror("fork");
		exit(-1);
	}
	return;
}


int print_cmd_prefix(void){
	struct passwd *mypwd = getpwuid(getuid());
	char *buff=(char*)malloc(sizeof(char)*128);
	getcwd(buff,128);
	printf("\033[33;1m%s@minishell\033[0m:\033[34;1m%s\033[0m>>> ",mypwd->pw_name,buff);
	free(buff);
	return 0;
}


int main(void){
	char str[STRLEN] ={0}; 
	char *args[ARGVLEN] = {NULL};
	while(1){
		print_cmd_prefix();  //printf xiaobo@ubuntu:$
		read_analyse_cmd(str,args); //reload args
		if(args[0]==NULL)  //only input '\n'
                	continue;
		if(read_analyse_buildin_cmd(args)==0) //check if buildin cmd
			goto here;
		run_cmd(args);
here:
		memset(str,0,sizeof(char)*STRLEN);
		memset(args,0,sizeof(char*)*ARGVLEN);
	}
	return 0;
}

	





/*
int main1(void){
	char *argv[ARGVLEN] = {NULL};
	char str[STRLEN] = {0};  //ls\0-a\0-l\0
	int i = 0;int j = 0;
	char *p = str;
	while(1){	
			
		unsigned char c = getchar();
		if(c==' ' || c=='\t' || c=='\n')
			if(i==0){
				if(c=='\n') break;  //exit when we have kong ge after last variable
				continue;
			}
			else{
				p[i++]='\0';
				argv[j++] = p;
				p +=i;
			       	i=0;
				if(c=='\n')break; //exit when we donot have kong ge after last variable	
			}
		else{
			p[i++] = c;
		}
			
	}
	
	//printf("%s %s %s\n", argv[0],argv[1],argv[2]);
	

	int p_stat = vfork();
	if(p_stat == 0){
		if(execvp(argv[0],argv) == -1){
			perror("execvp");
			_exit(-1);
		}
		_exit(0);
			
	}
	else if(p_stat > 0){
		wait(NULL);
	}
	else{
		perror("fork");
		exit(-1);
	}
	return 0;
}

*/
