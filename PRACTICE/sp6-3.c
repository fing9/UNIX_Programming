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
	int i, status, N=3;
	pid_t pid;

	for(i=0;i<N;i++) {
		pid = fork();
		if(pid == 0) {
			do_child(i);
		}
	}

	for(i=0;i<N;i++) {
		pid = wait(&status); //자식이 종료할때까지 기다린다.
		if(WIFEXITED(status)) { //만약 자식이 작업을 종료했다면.
			printf("%ld  ...  %d\n", pid, WEXITSTATUS(status)); //자식의 프로세스 아이디와 자식이 종료하면서 내뱉은 종료 코드를 출력한다.
		}
	}

	exit(0);
}
