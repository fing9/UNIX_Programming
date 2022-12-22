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
	char ch[100] = {0};

	mkdir("T1", 0700);
	chdir("T1");
	mkdir("T2", 0700);
	chdir("T2");
	mkdir("T3", 0700);
	chdir("T3");

	getcwd(ch, 99);
	printf("%s\n", ch);

	return 0;
}
