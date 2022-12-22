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

void catchsig();

void do_child(int n) {
	int i, pid;
	static struct sigaction act;
	
	act.sa_handler=catchsig;
	sigaction(SIGUSR1, &act, NULL);

	printf("%d-th child is created...\n", i);

	pause(); //signal을 받으면 pause에서 깨어난다.

	pid = getpid();
        for(i=0;i<3;i++) {
                printf("child %d .... \n", pid);
        }

	exit(n);
}

void catchsig() {
	return;
}

int main(void){
	int i, cid, status;
	pid_t pid[3];
	
	for (i=0;i<3;i++) {
		pid[i] = fork();
		if (pid[i]==0) {
			do_child(i);
			exit(i);
 		}
	}
	
	for(i=0;i<3;i++) {
		sleep(1);
		kill(pid[i], SIGUSR1);
	}

	for (i=0;i<3;i++){
		cid = wait(&status);
		printf("child id=%d, exit status=%d\n", cid, WEXITSTATUS(status));
	}

	exit(0);
}
