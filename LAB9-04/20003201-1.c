#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <ftw.h>
#include <string.h>
#include <stdio.h>

int list(const char *name, const struct stat *status, int type) {
	
	if (type==FTW_D) {
		printf("%s : %d\n", name, status->st_size);
	}
	else if(type==FTW_F) {
		if(S_IXUSR & status->st_mode || S_IXGRP & status->st_mode || S_IXOTH & status->st_mode)
			printf("%s : %d\n", name, status->st_size);
	}

	return 0;
}

int main(void) {

	ftw(".", list, 1);
		
	return 0;
}
