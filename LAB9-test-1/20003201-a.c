#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fd, i;
	char ch = 'X';

	fd=open("test1", O_WRONLY|O_CREAT, 0600);

	for(i=0;i<10;i++) {
		write(fd, &ch, sizeof(char));
	}

	return 0;
}
