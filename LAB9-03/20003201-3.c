#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(void){
	char str1[101], str2[101];
	scanf("%s", str1);
	scanf("%s", str2);

	symlink(str1, str2);	

	return 0;
}
