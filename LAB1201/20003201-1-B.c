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

int main(void) {
	ushort buf2[2] = {1, 0};
	int shmid, semid, i, n, *buf;
	key_t key1, key2;
	union semun arg;
	struct sembuf p_buf;

	key1=ftok("key", 99);
	semid=semget(key1, 2, 0600|IPC_CREAT|IPC_EXCL);
	
	if (semid==-1){
		semid=semget(key1, 2, 0);
	}
	else{
		arg.array=buf2;
		semctl(semid, 0, SETALL, arg);
	}

	key2=ftok("key", 122);
	shmid=shmget(key2, sizeof(int)*10, 0600|IPC_CREAT|IPC_EXCL);
	if(shmid == -1) {
		shmid = shmget(key2, sizeof(int)*10, 0600);
	}
	buf=(int *)shmat(shmid, 0, SHM_RDONLY);
	
	for(i=0;i<10;i++) {
		p_buf.sem_num = 1;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);

		printf("%d\n", *(buf+i), semid);

		p_buf.sem_num = 0;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}

	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID, 0);

	exit(0);
}

