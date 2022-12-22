#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fd, i, p, data[10]={0,};
	
	fd=open("test2", O_RDONLY);
	p=lseek(fd, 0, SEEK_SET);

	for(i=0;i<5;i++) {
		read(fd, &data[i], sizeof(int));
	}

	for(i=0;i<10;i++) {
		printf("%d", data[i]);
	}

	return 0;
}
