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

void catchalarm(int);

int main(void) {
	int i, num, sum=0;
	static struct sigaction act;
	
	// SIGALRM signal 처리가 가능하도록 설정
	act.sa_handler = catchalarm;
	sigaction(SIGALRM, &act, NULL);
	
	for (i=0;i<10;i++) {
		alarm(10);
		
		if(scanf("%d", &num) > 0) {
			alarm(0);
		}
		else {
			i--;
			continue;
		}
		
		sum += num;
		printf("sum=%d\n", sum);
	}
	
	exit(0);
}

void catchalarm(int signo) {
	printf("input !!! input !!! input !!!\n");
	alarm(10);
}

