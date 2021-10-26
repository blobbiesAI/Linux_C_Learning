#include <stdio.h>
#include <string.h>
#define ARGVLEN 32
#define STRLEN 128


void run_cmd(char *argv[]);

int run_script_cmd(char * pathname, char* str, char *args[]){

	FILE* script_file = fopen(pathname, "r");
	int i = 0;int j = 0;
        char *p = str; 
	char c = 0;

	while(1){
		c = getc(script_file);

		
		if(c==' ' || c=='\t' || c=='\n' || c=='|'){
                	if(i==0){
                        	if(c=='\n'){
					if(args[0]==NULL)  //only input '\n'
			                        continue;
                                	run_cmd(args);  //exit when we have kong ge after last variable
					memset(str,0,sizeof(char)*STRLEN);
					memset(args,0,sizeof(char*)*ARGVLEN);
					i =0;j=0;p=str;
				}
                                else if(c=='|')
                                        p[i++] = c;
                                continue;
                        }
                        else{
                                p[i++]='\0';
                                args[j++] = p;
                                p +=i;
                                i=0;
                                if(c=='\n'){
                                        run_cmd(args); //exit when we donot have kong ge after last variable
					memset(args,0,sizeof(char*)*ARGVLEN);
					memset(str,0,sizeof(char)*STRLEN);
					i=0;j=0;p=str;
				}
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
                      //  if(c=='&'){
                        //        is_background = 1;//creat a flag
                          //      continue;  //do not put & in args, it just a biaozhi
                       // }
			if(c==EOF){
			 	run_cmd(args);
				memset(str,0,sizeof(char)*STRLEN);
                                memset(args,0,sizeof(char*)*ARGVLEN);
				break;
			}
                        p[i++] = c;
                }
		
	}
	return 0;
}
