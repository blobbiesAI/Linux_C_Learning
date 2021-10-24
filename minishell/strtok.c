#include <string.h>
#include <stdio.h>
int main(void){
	char str[20] = "cat test.c | wc -l";
	char* token, *temp = str;

	
	while( (token = strtok(temp,"|"))!=NULL ){
		printf("%s\n",token);
		temp = NULL;
	}


	
	for(int i = 0;i<20;i++)
	{	
		if(str[i]=='\0'){
			printf("%d\n", 2);
			continue;
		}
		printf("%c\n",str[i]);
	}

	printf("%s\n",str);  //str = hello '\0' world'\0'wxb
	return 0;
}

