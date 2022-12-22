#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fd, i, data = 35;

	fd=open("test2", O_WRONLY|O_CREAT, 0640);

	for(i=0;i<10;i++) {
		write(fd, &data, sizeof(int));
	}

	return 0;
}
