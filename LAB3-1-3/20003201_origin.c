#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void cd_m(char **res) {
	//cd 명령 수행
	int ret;
	char cwd[512];
	ret = access(res[1], F_OK);
	if(ret == 0) {
		ret = chdir(res[1]);
		if(ret == 0) {
			ret = getcwd(cwd, 512);
			//printf("successfully changed into %s\n", cwd);
		}
		else
			printf("error : can't change current directory into %s.\n", res[1]);
	}
	else {
		printf("%s directory dosen't exist\n", res[1]);
	}
}

void mkdir_m(char **res) {
	//mkdir 명령 수행
	int ret;
	ret = mkdir(res[1], 0755); //기본 0755 퍼미션
	
	if(ret == 0) {
		//printf("successfully make %s directory.\n", res[1]);
	}
	else {
		printf("error : directory already exists or is incorrect.\n");
	}
}

void ls_m(char **res) {
	//ls 명령 수행
	char cwd[512], m[2] = ".\0", f[3] = "..\0";
	DIR* dir = NULL;
	struct dirent* dirEntry;
	struct stat s;
	
	getcwd(cwd, 512);

	if((dir = opendir(cwd)) == NULL) {
		exit(1);
	}
	
	
	
	if(res[1] == 0) {
		while((dirEntry = readdir(dir)) != NULL) {
			if(strcmp(dirEntry->d_name, m) && strcmp(dirEntry->d_name, f))
				printf("%s  ", dirEntry->d_name);
		}
		printf("\n");
	}
	else if(!strcmp(res[1], "-l")){
		//ls -l 옵션 명령 수행
		while((dirEntry = readdir(dir)) != NULL) {
			if(strcmp(dirEntry->d_name, m) && strcmp(dirEntry->d_name, f)) {
				stat(dirEntry->d_name, &s);
				printf("%o %d %ld %ld", s.st_mode&0777, s.st_ino, s.st_size, s.st_ctime);
				printf(" %s\n", dirEntry->d_name);
			}
		}
	}
}

void cp_m(char **res) {
	//cp 명령 수행
	int fd;
	
	fd = open(res[1], O_RDONLY|O_EXCL);

	if(fd == 0) {
		
	}
}

int main(void) {
	char name[100], in[50], *res[20]={0};
	int i;

	while(1) {
		printf("$ ");
		gets(in);
		i=0;
		res[i]=strtok(in, " ");
		while (res[i]) {
			i++;
			res[i]=strtok(NULL, " ");
		}

		if (!strcmp(res[0], "cd")) {
			cd_m(res);
		}
		else if (!strcmp(res[0], "mkdir")) {
			mkdir_m(res);
		}
		else if (!strcmp(res[0], "ls")) {
			ls_m(res);
		}
		else if (!strcmp(res[0], "cp")) {
			cp_m(res);
		}
		else
			exit(0);
	}
}





