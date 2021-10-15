#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	char *buff = (char*)malloc(sizeof(char)*20);
	read(0, buff, 20);//fd=0: stdin
	write(1, buff, 20);//fd=1: stdout
	return 0;
}
