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

int main() {
	char *const av[] = {"test1", "3", "5", "7", (char*)0};

	execv("./test1", av); //p를 안붙이면 ./을 붙이나 안붙이나 실행 잘된다.
	printf("execution(execv) fails..\n");
	exit(1);
}
