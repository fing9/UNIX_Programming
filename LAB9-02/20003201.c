#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	char ch1 = 'X', ch2 = 'Y', ch3 = 'Z', ch4 = 'T', ch5 = 'S', ch6 = 'W';
	int fd, i;
	fd = open("data1", O_RDWR|O_CREAT|O_TRUNC, 0644);

	for(i=0;i<10;i++) {
		write(fd, &ch1, 1);
	}
	
	lseek(fd, 0, SEEK_SET);
	write(fd, &ch2, 1);
	
	lseek(fd, 1, SEEK_END); //lseek(fd, 1, SEEK_END);
	write(fd, &ch2, 1);

	lseek(fd, 1, SEEK_SET);
	write(fd, &ch3, 1);
	lseek(fd, 3, SEEK_SET);
	write(fd, &ch3, 1);
	lseek(fd, 5, SEEK_SET);
	write(fd, &ch3, 1);
	lseek(fd, 7, SEEK_SET);
	write(fd, &ch3, 1);
	
	lseek(fd, 14, SEEK_SET);
	write(fd, &ch4, 1);

	lseek(fd, -2, SEEK_END);
	write(fd, &ch5, 1);
	
	lseek(fd, -3, SEEK_END); //lseek(fd, -2, SEEK_CUR);
	write(fd, &ch6, 1);
	
	return 0;
}
