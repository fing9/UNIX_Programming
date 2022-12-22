#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<ftw.h>
#include<time.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/shm.h>

void rm_m(char **res) {
	int cnt;
	struct stat s;
	struct dirent *d1, *d2;
	DIR *dp1, *dp2;

	dp1=opendir(res[1]);
	chdir(res[1]);

	while((d1 = readdir(dp1))!=NULL) {
		stat(d1->d_name, &s);

		if(S_ISREG(s.st_mode)) {
			remove(d1->d_name);
		}
		else {
			dp2=opendir(d1->d_name);
			cnt = 0;
			while((d2=readdir(dp2))!=NULL) {
				cnt++;
			}

			if(cnt == 2) {
				rmdir(d1->d_name);
			}
			else {
				if(strcmp(d1->d_name, ".") == 0 || strcmp(d1->d_name, "..") == 0) continue;
				printf("%s has %d files or directories\n", d1->d_name, cnt-2);
			}
		}
	}
	
	chdir("..");
	if(rmdir(res[1])==-1)
		printf("cannot remove %s\n", res[1]);
}

int main(void) {
	char in[100], *res[20] = {0};
	int i;

	while(1) {
		printf("> ");
		gets(in);
		if(in[0] == '\0')
			continue;
		i=0;
		res[i]=strtok(in, " ");
		while(res[i]) {
			i++;
			res[i]=strtok(NULL, " ");
		}

		if(strcmp(res[0], "exit")==0)
			exit(0);
		if(!strcmp(res[0], "rm")) {
			rm_m(res);
		}
	}
	
	return 0;
}

