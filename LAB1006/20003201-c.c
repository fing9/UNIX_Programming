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
	execlp("test2", "test2", "abc", "def", "ghi", (char *)0);
	exit(1);
}

int main(void) {
	pid_t pid;
	
	switch(pid=fork()) {
		case -1:
			printf("fork failed..\n");
			exit(0);
			break;
		case 0:
			do_child();
			break;
		default:
			wait(0);
			break;
	}
	
	
	
	return 0;
}
