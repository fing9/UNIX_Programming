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

int list(const char *name, const struct stat *status, int type) {
	if(type == FTW_F)
		printf("F % -30s\n", name);
	else if(type == FTW_D)
		printf("D % -30s\n", name);
	else if(type == FTW_DNR)
		printf("DNR % -30s\n", name);
	else if(type == FTW_SL)
		printf("SL % -30s\n", name);
	else if(type == FTW_NS)
		printf("NS % -30s\n", name);
	return 0;
}

int main() {
	ftw(".", list, 1);
	return 0;
}
