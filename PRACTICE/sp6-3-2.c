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

void do_child(int N) {
	int i;
	
	for(i=0;i<5;i++) {
		printf("child %ld running ...\n", getpid());
		sleep(1);
	}

	exit(N);
}

int main() {
	int i, n, status;
	pid_t pid;

	for(i=0;i<3;i++) {
		pid = fork();
		if (pid == 0){
			do_child(i);
		}
	}

	n = waitpid(pid, &status, 0);
	if (WIFEXITED(status)) {
		printf("%ld ... %d\n", n, WEXITSTATUS(status));
	}

	while(1) {
		n = waitpid(-1, &status, 0);
		if(n == -1) break;
		if(WIFEXITED(status))
			printf("%ld ... %d\n", n, WEXITSTATUS(status));
	}
	
	exit(0);
}
