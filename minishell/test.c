#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char** environ;
int main(void)
{	int env_num =0;
	char *minishell_var[100] = {NULL};
          char **p = environ;
          unsigned int slen;
          int i = 0;
          while(p[i]!=NULL){
                  slen = strlen(p[i]);
                  minishell_var[i] = (char*)malloc(sizeof(char)*(slen+1));//+1?
                  //strcpy(minishell_var[i],p[i]);
		  printf("%s\n", p[i]);
                  i++;
          }
          env_num = i;
 

	return 0;
}
