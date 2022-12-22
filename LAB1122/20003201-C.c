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
	int data;
};

int main(int argc, char **argv) {
	int i, qid, in, id;
	key_t key;
	struct q_entry msg;
	
	id=atoi(argv[1]);
	
	mkdir("key20003201", 0644);
	key=ftok("key20003201", 122);
	qid=msgget(key, IPC_CREAT|0600);
	
	for(i=0;i<5;i++) {
		scanf("%d", &in);
		msg.mtype = id;
		msg.data = in;
		msgsnd(qid, &msg, sizeof(int), id);
		msgrcv(qid, &msg, sizeof(int), id+8, 0);
		printf("%d\n", msg.data);
	}
	
	return 0;
}

