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

int main(void){
        char name[100], in[50], *res[20]={0};
        int i, status;
	pid_t pid;

        while (1){
		// current working directory의 이름을 출력
		getcwd(name, 100);
		while(name[i]) {
			i++;
		}
		name[i++] = '>';
		name[i++] = ' ';	
		name[i++] = '\0';         	

		write(1, name, i);

        	gets(in);
		if (in[0]=='\0')
			continue;

		i=0;
        	res[i]=strtok(in, " ");
		while (res[i]){
			res[++i]=strtok(NULL, " ");
		}

        	if (strcmp(res[0], "exit")==0){
        		exit(0);
		}
		// 실행파일을 실행하도록 필요한 코드 작성
		
        	if (!strcmp(res[0], "cat_m")){
        		pid = fork();
			if(pid == 0) {
				if(res[1] == NULL) {
					exit(0);
				}
				execlp("cat_m", res[0], res[1], (char *)0);
				exit(0);
			}
			
			wait(0);
		}
		else if (!strcmp(res[0], "cd_m")){
                        chdir(res[1]);
                }
                else if (!strcmp(res[0], "cp_m")){
                        pid = fork();
                        if(pid == 0) {
                                if(res[1] == NULL || res[2] == NULL) {
                                        exit(0);
                                }
                                execlp("cp_m", res[0], res[1], res[2], (char *)0);
				exit(0);
                        }

                        wait(0);
                }
                else if (!strcmp(res[0], "mkdir_m")){
                        pid = fork();
                        if(pid == 0) {
                                if(res[1] == NULL) {
                                        exit(0);
                                }
                                execlp("mkdir_m", res[0], res[1], (char *)0);
                        }

                        wait(0);
                }
                else if (!strcmp(res[0], "ls_m")){
                        pid = fork();
                        if(pid == 0) {
                                execlp("ls_m", res[0], (char *)0);
                        }

                        wait(0);       
                }
                else if (!strcmp(res[0], "rm_m")){
                        pid = fork();
                        if(pid == 0) {
                                if(res[1] == NULL) {
                                        exit(0);
                                }
                                execlp("rm_m", res[0], res[1], (char *)0);
                        }

                        wait(0);
                }
		else {// user exe file
                        pid = fork();
                        if(pid == 0) {
				res[++i] = (char*)0;
				strcpy(in, res[0]);
                                execv(in, res);
                        }

                        wait(0);
		}
	}

	return 0;
}


/*
 *if(strcmp(res[0], "exit"==0))
 *	exit(0);
 * }
 *else if(strcmp(res[0], "cd_m")==0)
 *	chdir(res[1]);
 *else{
 *	if ((pid=fork())== 0) {
 *		execvp(res[0], &res[1]);
 *		exit(0);
 *	}
 *	else {
 *		wait(&status); //hang sang fork() han man km wait
 *	}
 *}
