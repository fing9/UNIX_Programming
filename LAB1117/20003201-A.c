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
	char f[2][3] = {"f1", "f2"};
	int i, in, fd[2];

	// FIFO 2개 만들기
	// "f1"과 "f2" open
	for (i=0;i<2;i++) {
		mkfifo(f[i], 0600);
		fd[i] = open(f[i], O_RDWR);
	}
	
	for(;;) {
		scanf("%d", &in);
		// "f1"으로 정수 보내기
		write(fd[0], &in, sizeof(int));
		if (in == -1)
			exit(0);
		// "f2"애서 정수 읽기
		read(fd[1], &in, sizeof(int));
		printf("%d\n", in);
	}

	return 0;
}

