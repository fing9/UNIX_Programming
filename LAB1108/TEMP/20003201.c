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
pid_t pid[2]={0};

void catchalarm(int signo);

int main(void){
        char in[50], *res[20]={0};
        int i, status;
	static struct sigaction act;

        // 필요한 signal 설정
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	
	act.sa_handler = catchalarm;
	sigaction(SIGALRM, &act, NULL);
	
	// backup_m 실행을 위해 필요한 작업
	pid[1] = fork();
	if(pid[1] == 0) {
		execlp("backup_m", "backup_m", (char *)0);
		exit(0);
	}
	
        while (1){
               	printf("> ");
        	gets(in);
		if (in[0]=='\0')
			continue;

		i=0;
        	res[i]=strtok(in, " ");
		while (res[i]){
			res[++i]=strtok(NULL, " ");
		}

        	if (strcmp(res[0], "exit")==0){
			// 실행 중인 backup_m 종료 확인
			if (waitpid(pid[1], &status, WNOHANG) == 0) {
				waitpid(pid[1], &status, 0);
			}
        		
			exit(0);
		}
		else if (strcmp(res[0], "cd_m")==0)
			chdir(res[1]);
		else{
			if ((pid[0]=fork())==0){
				// signal 처리 설정
				act.sa_handler = SIG_DFL;
				sigaction(SIGINT, &act, NULL);
				// child가 명령 실행
				execvp(res[0], res);
				exit(0);
			}
			else{
				// child의 종료 확인
				waitpid(pid[0], &status, 0);
			}
		}
		in[0] = NULL;

		// backup 종료 확인
		if (waitpid(pid[1], &status, WNOHANG) > 0) {
			// 종료 했으므로 20초 후 다시 backup 실행
			alarm(20);
		}
	}

	return 0;
}

void catchalarm(int signo){
	// alarm 처리
        pid[1] = fork();
        if(pid[1] == 0) {
                execlp("backup_m", "backup_m", (char *)0);
		exit(0);
        }
}
