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

void sigbreak();

void do_child(int i, int *cid) {
	int j;
	pid_t pid;
	static struct sigaction act;

	act.sa_handler = sigbreak;
	sigaction(SIGUSR1, &act, NULL);

	if(i < 4) {
		pause();
	}
	
	pid = getpid();
	for(j=0;j<5;j++) {
		printf("child %d .... \n", pid);
		sleep(1);
	}

	if(i > 0) {
		kill(cid[i-1], SIGUSR1);
	}

	exit(0);
}

void sigbreak() {
	return;
}

int main(void) {
	int i, status;
	pid_t pid[5];

	for (i=0;i<5;i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			do_child(i, pid);
		}
	}

	for (i=0;i<5;i++) {
		wait(&status);
	}

	exit(0);
}

