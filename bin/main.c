pid_t pid[2]={0};

void catchalarm(int signo);

int main(void){
        char in[50], *res[20]={0};
        int i, status;
	static struct sigaction act;

        // 필요한 signal 설정

	// backup_m 실행을 위해 필요한 작업

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
        		exit(0);
		}
		else if (strcmp(res[0], "cd_m")==0)
			chdir(res[1]);
		else{
			if ((pid[0]=fork())==0){
				// signal 처리 설정
				// child가 명령 실행
				exit(0);
			}
			else{
				// child의 종료 확인
			}
		}

		// backup 종료 확인
	}

	return 0;
}

void catchalarm(int signo){
	// alarm 처리
}
