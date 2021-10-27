#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>
#include <pwd.h>
#include <signal.h>

#include <unistd.h>
#include <fcntl.h>
#include "buildin_cmd.h"
//#include "variable_cmd.h"
#include "variable_cmd_v2.h"

#define ARGVLEN 32
#define STRLEN 128
#define SPLITLEN 10
#define ENVMASIZE 10
int is_background=0;
int env_num = 0;
void read_analyse_cmd(FILE* f ,char *str, char *args[]){
	//char str[STRLEN] = {0};  //ls\0-a\0-l\0
	int i = 0;int j = 0;
	char *p = str;
	char c = 0;
	while(1){	
		c = getc(f);	
		//c = getchar();   //loop stop here, to wait for stdin input
		if(c==' ' || c=='\t' || c=='\n' || c=='|'){
			if(i==0){
				if(c=='\n') 
					break;  //exit when we have kong ge after last variable
				else if(c=='|')
					p[i++] = c;
				continue;
			}
			else{
				p[i++]='\0';
				args[j++] = p;
				p +=i;
			       	i=0;
				if(c=='\n')
					break; //exit when we donot have kong ge after last variable	
				else if(c=='|'){
					p[i++] = c;
					p[i++] = '\0';
					args[j++] = p;
					p +=i;
					i=0;
				}
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

//	for(int m=0;m<5;m++){
//		printf("%s\n",args[m]);
//	}

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




int split_args(int split_id[], char *args[]){
	int i = 0;
	int j = 1;
	while(args[i]!=NULL){
		if(strcmp(args[i],"|")==0){
			args[i] = NULL;	
			split_id[j++] = i+1;		
		}
		i++;
	}
	return j;
}


int run_pipe_cmd(int fork_num, int split_id[], char *args[]){
	int pipefd[2]={0};
	int pipefd2[2]={0};
	int p_stat;

	pipe(pipefd);
	//pipe(pipefd2);
	for(int pro =0;pro< fork_num;pro++){
		p_stat = fork();
		if(p_stat==0){
			if(pro %2 ==0){
				if(pro!=0)
					dup2(pipefd2[0],0);
				if(pro!=fork_num-1)
					dup2(pipefd[1],1);
				execvp(args[split_id[pro]],args+split_id[pro]);
			}
			else{
				dup2(pipefd[0],0);
				if(pro!=fork_num-1)
					dup2(pipefd2[1],1);
				execvp(args[split_id[pro]],args+split_id[pro]);
			}
		}
		else if(p_stat>0){
			wait(NULL);
			if(pro %2 ==0){
				close(pipefd[1]);
				pipe(pipefd2);
			}
			else{
				close(pipefd2[1]);
				pipe(pipefd);
			}
			
		}
		else{
			perror("fork");
			exit(-1);
		}
	}
	return 0;
}




/*
	pipe(pipefd); // 3 4
	p_stat = fork();
	if(p_stat ==0){
		dup2(pipefd[1],1);
		execvp(args[split_id[0]],args+split_id[0]);			
	}
	else if(p_stat >0){ 
		wait(NULL);
		close(pipefd[1]);
	}
	else{
		perror("fork 1");
		exit(-1);
	}
	// 3

	


	pipe(pipefd2);//3 4 5
	cp_stat = fork();
        if(cp_stat==0){
               	dup2(pipefd[0],0);
		dup2(pipefd2[1],1);
              	execvp(args[split_id[1]],args+split_id[1]);
        }
 
        else if(cp_stat > 0){ 
		wait(NULL);
		close(pipefd[0]);//close
		close(pipefd2[1]);
	}
	else{
		perror("fork 2");
		exit(-1);
	}






	//while(1); 4
	//int pipefd3[2]={0};
	pipe(pipefd);
	// 3 4 5
	p_stat = fork();
	if(p_stat==0){
		dup2(pipefd2[0],0);
		dup2(pipefd[1],1);
		execvp(args[split_id[2]],args+split_id[2]);
	}
	else if(p_stat>0){
		wait(NULL);
		close(pipefd2[0]);  //2 close
		//while(1);// 3 5
		close(pipefd[1]);
	}
	else{
		perror("fork3");
		exit(-1);
	}
	//while(1);3
	cp_stat = fork();
	if(cp_stat==0){
		dup2(pipefd[0],0);
		execvp(args[split_id[3]],args+split_id[3]);
	}
	else if(cp_stat>0){
		wait(NULL);
		close(pipefd[0]);
	}
	
*/	
	





/*
int run_pipe_cmd(int fork_num, int split_id[], char *args[]){
	int pipefd[2]={0};
	pipe(pipefd);
	int p_stat, cp_stat;	
	p_stat = fork();
	
	if(p_stat ==0){
		//close(pipefd[0]);
		dup2(pipefd[1],1);
		execvp(args[split_id[0]],args+split_id[0]);
		
		
			
	}
	else if(p_stat >0){ 
		wait(NULL);
		close(pipefd[1]);
		cp_stat = fork();
	        if(cp_stat==0){
                	//close(pipefd[1]);
                 	dup2(pipefd[0],0);
                 	execvp(args[split_id[1]],args+split_id[1]);
			
            
        	 }
 
         	else if(cp_stat > 0){ 
			wait(NULL);
		}

	}


	return 0;
}

*/
int run_script_cmd(char *pathname, char* str, char *args[]);

int main(void){
	char str[STRLEN] ={0}; 
	char *args[ARGVLEN] = {NULL};
	int split_id[SPLITLEN] = {0};
	int fork_num = 1;

	//script
	char script_str[STRLEN] ={0};
        char *script_args[ARGVLEN] = {NULL};

	//env
	//env wxb_env[ENVMASIZE]={0};
	char *minishell_var[100] = {NULL};
	env_init_cmd(minishell_var);

	while(1){
		print_cmd_prefix();  //printf xiaobo@ubuntu:$
		read_analyse_cmd(stdin, str,args); //reload args
		if(args[0]==NULL)  //only input '\n'
                	continue;
		if(read_analyse_buildin_cmd(args, minishell_var)==0) //check if buildin cmd
			goto here;
		
		fork_num = split_args(split_id, args);

		//for(int m =0;m<10;m++){
		//	printf("%d ",split_id[m]);
		//}

		if(fork_num==1){
			if(strstr(args[0],".sh"))
				run_script_cmd(args[0],script_str,script_args);
			else if(is_variable_cmd(args)){
				run_variable_cmd(args, minishell_var);
			}
			else
				run_cmd(args);
		}
		else
			run_pipe_cmd(fork_num, split_id, args);
here:
		memset(str,0,sizeof(char)*STRLEN);
		memset(args,0,sizeof(char*)*ARGVLEN);
		memset(split_id,0,sizeof(int)*SPLITLEN);
		
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
