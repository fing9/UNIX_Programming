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
	struct stat buf;

	stat("test4", &buf);
	printf("%o, %ld\n", buf.st_mode&0777, buf.st_size);
	printf("%s\n", ctime(&buf.st_mtime));
	
	lstat("test4", &buf);
	printf("%o, %ld\n", buf.st_mode&0777, buf.st_size);
	printf("%s\n", ctime(&buf.st_mtime));

	return 0;
}
