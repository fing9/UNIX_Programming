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
	int fd;
	pid_t pid;
	char buf[10];

	fd = open("data", O_RDONLY);
	read(fd, buf, 10);
	printf("before fork : %ld\n", lseek(fd, 0, SEEK_CUR));
	switch(pid=fork()) {
		case -1:
			perror("fork failed\n");
			exit(1);
			break;
		case 0:
			printf("child before read : %ld\n", lseek(fd, 0, SEEK_CUR));
			read(fd, buf, 10);
			printf("child after read : %ld\n", lseek(fd, 0, SEEK_CUR));
		default:
			wait(0);
			printf("parent after wait : %ld\n", lseek(fd, 0, SEEK_CUR));
			
	}

	return 0;
}
