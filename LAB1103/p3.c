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

void catchusr(int);

void do_child(void) {
	int i, pid, gid;
	static struct sigaction act;
	
	// SIGUSR1 처리 가능하도록 설정
	act.sa_handler = catchusr;
	
	// 본 process와 자신의 child process가 같이 signal을 받을 수 있도록 설정
	sigaction(SIGUSR1, &act, NULL);
	setpgid(getpid(), getpid());
	
	pid = fork();
	// SIGUSR1이 올 때까지 대기
	pause();
	
	gid=getpgid(0);
	for(i=0;i<3;i++) {
		printf("group id=%d .... process id=%d\n", gid, getpid());
		sleep(1);
	}	

	if(pid>0)
		pid=wait(0);
	exit(0);
}

int main(void) {
	int i;
	pid_t pid[2];

	for(i=0;i<2;i++) {
		pid[i] = fork();
		if (pid[i] == 0) {
			do_child();
		}
	}

	sleep(2);
	// 첫 번째 child와 그 child의 child에게 SIGUSR1 보내기
	kill(-pid[0], SIGUSR1);	

	sleep(5);
	// 두 번째 child와 그 child의 child에게 SIGUSR1 보내기
	kill(-pid[1], SIGUSR1);
	
	for (i=0;i<2;i++)
		wait(0);
		
	exit(0);
}

void catchusr(int signo) {
}
