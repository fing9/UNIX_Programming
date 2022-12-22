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
	char buf[512];

	fd = open("data", O_RDONLY);

	for(i=0;i<10;i++) {
		read(fd, buf, 1);
		printf("%c\n", buf[0]);
		sleep(1);
	}
	
	return 0;
}

