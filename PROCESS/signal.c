#include <signal.h>
#include <stdio.h>


//kill -l

typedef void (*sighandler_t)(int);

struct signal_class{
	int signum;
	sighandler_t handler;
};

void add(int a){
	printf("%d\n",a);
	return;
}

void sub(int a){
	printf("%d\n",a);
	return;
}


int main(void){
	struct signal_class handler;
	handler.signum = SIGINT;handler.handler = add;
	signal(handler.signum, handler.handler);

	handler.signum = SIGHUP;handler.handler = add;
	signal(handler.signum, handler.handler);
	pause();
	//while(1);
	return 0;
}
