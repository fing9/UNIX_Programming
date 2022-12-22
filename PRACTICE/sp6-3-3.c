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

int main(void) {
	int i, n, status;
	pid_t pid;

	pid = fork();
	if(pid == 0) {
		do_child(25);
	}

	while(1) {
		n = waitpid(pid, &status, WNOHANG);
		if(n>0) { //기다림이 끝남
			if(WIFEXITED(status))
				printf("%ld ... %d\n", n, WEXITSTATUS(status));
		}
		else if(n == 0)
			printf("waiting....\n"); //기다리는중
		else //기다림이 끝난 다음 루프
			break;
		sleep(1); //준내 빨리 계속 확인하지 않기위해서 다른 작업을 하고있는 시간이라고 가정하고 기다림
	}

	exit(0);
}
