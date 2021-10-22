#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
typedef struct msgbuff{
	long mtype;  //must same as example, otherwise message queue do not konw the sended message type.
	char mtext[20];
}msgbuff;

int main(void){
	key_t msg_key = ftok(".", 123);
	int p_stat = vfork();
	if(p_stat == 0){
		int msg_id = msgget(msg_key, IPC_CREAT|0666);
		if(msg_id==-1){
			perror("msgget error");
			_exit(-1);
		}
		msgbuff mymsg = {4,"hello world"};
	 	int snd_stat = msgsnd(msg_id, &mymsg, sizeof(mymsg.mtext), IPC_NOWAIT);
		if(snd_stat==-1){
			perror("msgsnd error");
			_exit(-1);
		}
		printf("%s\n",mymsg.mtext);
	//	msgctl(msg_id, IPC_RMID,NULL);
		_exit(0);
	}
	else if(p_stat >0){
		wait(NULL);
		int msg_iid = msgget(msg_key, IPC_CREAT|0666);
		msgbuff *rcvmsg = (msgbuff*)malloc(sizeof(msgbuff));
		int rcv_stat = msgrcv(msg_iid, rcvmsg, sizeof(rcvmsg->mtext), 4, IPC_NOWAIT);
		if(rcv_stat==-1){
			perror("msgrcv error");
			exit(-1);
		}
		printf("%s\n", rcvmsg->mtext);
		free(rcvmsg);
		msgctl(msg_iid, IPC_RMID, NULL);
	}
	return 0;
}
