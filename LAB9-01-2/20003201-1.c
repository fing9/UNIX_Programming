#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	int fd, i;
	char ch = 'K';

	fd = open("test1", O_WRONLY|O_CREAT|O_EXCL ,0644);
	if(fd == -1) {
		printf("open error ...........\n");
	}
	else {
		for(i = 0;i<10;i++) {
			write(fd, &ch, sizeof(int));
		}	
	}

	return 0;
}
