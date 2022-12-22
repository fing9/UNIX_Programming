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

struct buffer{
	int f, r;
	char msg[10][512];
};

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(void) {
	char temp[512];
	ushort buf[3]={10, 0, 1}; //세마포 3개가 필요함 | {producer가 쓸 수 있는 버퍼의 수, consumer가 쓸 수 있는 버퍼의 수, producer-consumer 상호베타}
	int i, fd, n, semid, shmid;
	key_t key1, key2;
	union semun arg;
	struct buffer *msg_buf;
	struct sembuf p_buf;
	
	key1 = ftok("key", 50);
	// 세마포 생성
	semid = semget(key1, 3, 0600|IPC_CREAT|IPC_EXCL);
	if(semid == -1) {
		semid = semget(key1, 3, 0);
	}
	else {
		arg.array = buf;
		semctl(semid, 0, SETALL, arg);
	}

	key2=ftok("key", 20);
	// 공유 메모리 생성
	shmid = shmget(key2, sizeof(struct buffer), 0600|IPC_CREAT|IPC_EXCL);
	if(shmid == -1) {
		shmid = shmget(key2, sizeof(struct buffer), 0);
	}
	msg_buf = shmat(shmid, 0, 0);
	msg_buf->f=msg_buf->r = 0;

	do{
		scanf("%s", temp);
		
		// 세마포 웨이트 2개
		// semwait(0);
		p_buf.sem_num = 0;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		// semwait(2);
		p_buf.sem_num = 2;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		
		// temp를 shared memory에 복사
		strcpy(msg_buf->msg[msg_buf->r], temp);

		printf("idx=%d : msg=%s\n",
				msg_buf->r,
				msg_buf->msg[msg_buf->r]);
		// shared memory의 index 조정
		msg_buf->r = (msg_buf->r + 1) % 10;

		// 세마포 시그널 2개
		// semsig(2);
		p_buf.sem_num = 2;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		// semsig(1);
		p_buf.sem_num = 1;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}while (strcmp(temp, "quit"));

	exit(0);
}

