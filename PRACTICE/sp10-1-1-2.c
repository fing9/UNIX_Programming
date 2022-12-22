#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<ftw.h>
#include<time.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/shm.h>

struct q_entry{
	long mtype;
	int mnum;
};

int main(void) {
	int i, qid;
	key_t key;
	struct q_entry msg;

	key=ftok("key", 122);
	qid=msgget(key, IPC_CREAT|0600);
	
	for(i=0;i<3;i++) {
		msgrcv(qid, &msg, sizeof(int), 0, 0);
		printf("%d\n", msg.mnum);
	}
	
	return 0;
}
