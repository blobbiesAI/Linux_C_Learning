#include <unistd.h>
#include <stdio.h>
int main(void){
	char buff[128];
	getcwd(buff, 128);
	printf("%s", buff);
	return 0;
}
