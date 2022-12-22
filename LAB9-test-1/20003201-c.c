#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fd, i;
	char ch = 'Y';

	fd=open("test1", O_WRONLY);

	for(i=0;i<5;i++) {
		write(fd, &ch, sizeof(char));
	}

	return 0;
}
