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

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(void){
	ushort buf[2]={1, 0};
	int i, j, pid, semid;
	key_t key;
	union semun arg;
	struct sembuf p_buf;
	
	key=ftok("key", 224);
	semid=semget(key, 2, 0600|IPC_CREAT|IPC_EXCL);
	if (semid==-1){
		semid=semget(key, 2, 0);
	}
	else{
		arg.array=buf;
		semctl(semid, 0, SETALL, arg);
	}

	pid=getpid();
	for (i=0; i<3; i++){
		//wait(e)
		p_buf.sem_num = 1;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		//wait(s)
		p_buf.sem_num = 0;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);

		for (j=0; j<3; j++){
			printf("%d ... %ld\n", i, pid);
			sleep(1);
		}

		//sig(e)
		p_buf.sem_num = 1;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		//sig(s)
		p_buf.sem_num = 0;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}

	semctl(semid, 0, IPC_RMID, 0);

	return 0;
}
