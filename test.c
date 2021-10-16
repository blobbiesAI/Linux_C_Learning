#include <string.h>
#include <stdio.h>

int main(void){
	char * p ="cat.c";
	if(strstr(p,".c")){
		printf("yes\n");
	}
	return 0;
}
