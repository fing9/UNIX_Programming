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

int main(void) {
	char name[512], in[50], *res[20] = {0};
	int i, status;
	pid_t pid[2];
	int n, run = 0;

	while(1) {
		getcwd(name, 512);
		i = 0;
		while(name[i]) {
			i++;
		}
		name[i++] = '>';
		name[i++] = ' ';
		name[i++] = '\0';
		write(1, name, i);

		gets(in);
		if(in[0] == '\0') continue;

		i = 0;
		res[i] = strtok(in, " ");
		while(res[i]) {
			res[++i] = strtok(NULL, " ");
		}

		if(strcmp(res[0], "exit") == 0) {
			if(run == 1) {
				n = waitpid(pid[1], &status, WNOHANG);
				if(n == 0) {
					continue;
				}
			}
			exit(0);
		}
		else if(strcmp(res[0], "cd_m") == 0) {
			chdir(res[1]);
		}
		else if(strcmp(res[0], "backup_m") == 0) {
			if((pid[1]=fork()) == 0) {
				execvp(res[0], res);
				exit(0);
			}
			run = 1;
		}
		else {
			if((pid[0]=fork()) == 0) {
				execvp(res[0], res);
				exit(0);
			}
			else {
				waitpid(pid[0], &status, 0);
			}
		}

		if(run == 1) {
			n = waitpid(pid[1], &status, WNOHANG);
			if(n>0) {
				run = 0;
			}
		}
	}	

	return 0;
}

