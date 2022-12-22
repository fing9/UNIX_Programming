#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <ftw.h>
#include <string.h>
#include <stdio.h>

int list(const char *name, const struct stat *status, int type) {
	int cnt;
	struct dirent *d;
	DIR *dp;
	
	if (type==FTW_D || type==FTW_DNR) {
		if((dp = opendir(name)) == NULL)
			return 0;
		
		cnt = 0;
		while((d = readdir(dp)) != NULL)
			cnt++;
		
		if(cnt == 2)
			printf("%s\n", name);
	}

	return 0;
}

int main(void) {

	ftw(".", list, 1);
		
	return 0;
}
