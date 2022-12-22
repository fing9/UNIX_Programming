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
	int fd, i;
	int *addr;

	fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0600);
	addr = mmap(NULL, 50, PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, 50);
	
	for(i=0;i<10;i++) {
		scanf("%d", addr+i);
	}
	
	exit(0);
}

