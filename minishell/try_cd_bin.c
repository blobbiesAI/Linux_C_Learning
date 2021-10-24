#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
/*
enum buildin_cmd{
	cd=0, wxb
}bash_buildin_cmd;

int build_cd(char []);

int main(int argc, char *argv[]){
	printf("please input your cmd(0:cd,1:exit)\n");
	scanf("%u",&bash_buildin_cmd);

	switch(bash_buildin_cmd){
		case cd :
			build_cd(argv[1]);
			break;
		default:
			printf("error");
	};
	return 0;
}
*/


int main(void){
	chdir("..");
	printf("current working directory: %s\n", getcwd(NULL, 0));//when you run chdir function,you jiust change the child process(a.out) working dir, when you exit the child process\
	                                                             the parent working dir donot change.So we cannot get a elf file named cd, and use execvp to run it, it run in the child process\
							            We should put the chdir function in parent process code.That is why Linux donot supply a elf file named cd.They put it into the shel                                                                    l code ,called buildin function.
	                                                
	mkdir("www", 0777);
	return 0;

}
