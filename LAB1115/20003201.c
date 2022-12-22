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
#define MSGSIZE 6
char *msg1 = "hello";
char *msg2 = "bye!!";
void parent(int[][2]);
int child(int[]);


int main(void) {
	int pip[3][2];
	int i;

	for (i=0;i<3;i++) {
		pipe(pip[i]);
		if (fork()==0)
			child(pip[i]);
	}
	parent(pip);
	for (i=0;i<3;i++) {
		wait(0);
	}
		
	exit(0);
}



void parent(int p[3][2]) {
	char buf[MSGSIZE], ch;
	fd_set set, master;
	int i, j, k, n;
	struct timeval tv;
	
	tv.tv_sec = 10;
	tv.tv_usec = 0;

	for (i=0;i<3;i++) {
		close(p[i][1]);
	}
	FD_ZERO(&master);
	for (i=0;i<3;i++) {
		FD_SET(p[i][0], &master);
	}

	while (set=master, select(p[2][0] + 1, &set, NULL, NULL, &tv) > 0) {
		for (i=0;i<3;i++) {
			if (FD_ISSET(p[i][0], &set)) {
				if ((n=read(p[i][0], buf, MSGSIZE)) > 0)
					printf("MSG from %d=%s\n", i, buf);
				else if (n == 0){
					close(p[i][0]);
					FD_CLR(p[i][0], &master);
				}
			}
		}
		tv.tv_sec = 10;
	}
}

int child(int p[2]) {
	int count;

	close(p[0]);
	for (count=0; count<2; count++) {
		write(p[1], msg1, MSGSIZE);
		sleep(getpid()%4);
	}
	write(p[1], msg2, MSGSIZE);
	exit(0);
}
