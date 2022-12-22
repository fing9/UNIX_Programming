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

void do_child(void) {
	printf("pid=%ld ... gid=%ld ... sid=%ld\n", getpid(), getpgrp(), getsid(0));
	exit(0);
}

int main (int argc, char** argv) {
	int num, i;
	pid_t pid;

	num=atoi(argv[1]);
	for(i=0;i<num;i++) {
		pid = fork();
		if(pid==0)
			do_child();
	}

	for(i=0;i<num;i++) {
		wait(0);
	}

	return 0;
}
