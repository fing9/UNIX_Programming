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

int main(void) {
	int i, status;
	pid_t pid;

	for(i=0;i<3;i++) {
		pid = fork();
		if(pid == 0 && i == 0) {
			execl("./p1-a", "p1-a", "this", "is", "string", (char*)0);
			exit(0);
		}
		else if(pid == 0 && i == 1) {
			execl("./p1-b", "p1-b", (char*)0);
			exit(0);
		}
		else if(pid == 0 && i == 2) {
			execl("./p1-c", "p1-c", (char*)0);
			exit(0);
		}
	}	
	
	for(i=0;i<3;i++) {
		pid = wait(&status);
		if(WIFEXITED(status)) {
			printf("%ld ...... %d\n", pid, WEXITSTATUS(status));
		}
	}
	exit(0);
	return 0;
}

