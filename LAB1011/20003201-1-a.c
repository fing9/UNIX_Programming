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

int main(int argc, char** argv) {
	int i, j;

	for(i=0;i<5;i++) {
		j = 1;
		while(argv[j] != NULL) {
			printf("%s ", argv[j]);
			j++;
		}
		printf("\n");
		sleep(1);
	}
	
	
	return 0;
}

