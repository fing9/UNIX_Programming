#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fd, i, p;
	char ch = 'Z';

	fd=open("test1", O_WRONLY);
	p=lseek(fd, 0, SEEK_END);

	for(i=0;i<5;i++) {
		write(fd, &ch, sizeof(char));
	}

	return 0;
}
