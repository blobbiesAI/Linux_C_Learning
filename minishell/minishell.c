#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define ARGVLEN 32
#define STRLEN 128


void read_analyse_cmd(char *str, char *args[]){
	//char str[STRLEN] = {0};  //ls\0-a\0-l\0
	int i = 0;int j = 0;
	char *p = str;
	char c = 0;
	while(1){	
			
		c = getchar();
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
			p[i++] = c;
		}
			
	}
	return;	
}


void run_cmd(char *argv[]){
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
	return;
}

int main(void){
	char str[STRLEN] ={0}; 
	char *args[ARGVLEN] = {NULL};
	while(1){
		read_analyse_cmd(str,args);
		run_cmd(args);
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
