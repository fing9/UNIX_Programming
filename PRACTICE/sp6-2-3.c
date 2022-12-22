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

void do_child() {
	char *const av[] = {"test3", "3", (char)0};

	printf("* child %ld before execution ...\n", getpid());
	execv("./test3", av);
	exit(0);
}

int main() {
	int i, status, N=3;
	pid_t pid;

	for(i=0;i<N;i++) {
		pid = fork();
		if(pid == 0) {
			do_child();
		}
	}

	for(i=0;i<5;i++) {
		printf("*** parent %ld running ...\n", getpid());
		sleep(1);
	}

	for(i=0;i<N;i++) {
		wait(0);
	}

	exit(0);
}
