#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(void){
	struct stat buf, buf2;
	char str[101], str2[101];
	scanf("%s", str);
	
	lstat(str, &buf);
	printf("%s | %o | %ld\n", str, buf.st_mode&0777, buf.st_size);

	readlink(str, str2, 101);
	stat(str, &buf2);
	printf("%s | %o | %ld\n", str2, buf2.st_mode&0777, buf2.st_size);
	
	return 0;
}
