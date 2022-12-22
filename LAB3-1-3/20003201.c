#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void cd_m(char **res) {
	int ret;
	char cwd[512];
	ret = access(res[1], F_OK);
	if(ret == 0) {
		ret = chdir(res[1]);
		if(ret == 0) {
			ret = getcwd(cwd, 512);
		}
		else
			printf("error : can't change current directory into %s.\n", res[1]);
	}
	else {
		printf("%s directory dosen't exist\n", res[1]);
	}
}

void mkdir_m(char **res) {
	int ret;
	ret = mkdir(res[1], 0755);
	
	if(ret == -1) {
		printf("error : directory already exists or is incorrect.\n");
	}
}

void ls_m(char **res) {
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
	int fd, fd2, ret;
	char buf[512]
	struct stat s;
	
	fd = open(res[1], O_RDONLY);
	
	if(fd == -1 || res[1] == 0 || res[2] == 0) {
		printf("error : no file name.\n");
		return;
	}

	if(fstat(fd, &s) == -1) {
		printf("error : permition denied.\n");
		return;
	}

	fd2 = open(res[2], O_WRONLY|O_CREAT|O_TRUNC, s.st_mode&0777);
	
	if(fd != -1 && fd2 != -1) {
		do {
			ret = read(fd, buf, 512);
			write(fd2, buf, ret);
		} while(ret > 0);
	}
}

void chmod_m(char **res) {
	int fd, ret,  mod = 0, i = 0;
	
	if(res[1] == 0 || res[2] == 0) {
		printf("error : no file name.\n");
		return;
	}
	
	while(res[1][i] != NULL) {
		mod *= 8;
		mod += res[1][i] - '0';
		i++;
	}
	
	if ((fd = open(res[2], O_RDONLY)) == -1) {
		printf("error : can't open file.\n");
		return;
	}

	if((ret = fchmod(fd, mod)) == -1) {
		if((ret = chmod(res[1], mod)) == -1) {
			printf("error : chmod failed.\n");
			return;
		}
	}
}

void cat_m(char **res) {
	int fd, ret, i;
	char buf[512];

	if((fd = open(res[1], O_RDONLY)) == -1) {
		printf("error : can't read file.\n");
		return;
	}
	
	do {
		ret = read(fd, buf, 512);
		for(i=0;i<ret;i++) {
			printf("%c", buf[i]);
		}
	} while(ret > 0);
}

void rm_m(char **res) {
	if(remove(res[1]) == -1) {
		printf("error : remove failed.\n");
		return;
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
		else if (!strcmp(res[0], "chmod")) {
			chmod_m(res);
		}
		else if (!strcmp(res[0], "cat")) {
			cat_m(res);
		}
		else if (!strcmp(res[0], "rm")) {
			rm_m(res);
		}
		else
			exit(0);
	}
}

