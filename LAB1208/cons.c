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
	int f, r; // f : 다음번에 데이터를 쓸 위치, r : 다음번에 데이터를 읽어갈 위치| 쓰고서 ++ 해주고 모듈러연산으로 원형으로 구현 해야함
	char msg[10][512];
};

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(void) {
	char in[10], temp[512]="";
	ushort buf[3]={10, 0, 1}; //세마포 3개가 필요함 | {producer가 쓸 수 있는 버퍼의 수, consumer가 쓸 수 있는 버퍼의 수, producer-consumer 상호베타}
	int i, fd, n, semid, shmid;
	key_t key1, key2;
    union semun arg; // arg : 초기화할 때 세마포 초기 값을 넣는 변수
	struct buffer *msg_buf; // msg_buf : 공유 메모리의 메모리 공간을 할당받아 선언된 변수
	struct sembuf p_buf; // p_buf : semctl을 하기 위해 세마포인덱스/조작할값/IPC_NOWAIT할 지

	key1=ftok("key", 50);
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
	
	while(1) {
		scanf("%s", in);
		
		// 세마포 웨이트 2개
		// semwait(1);
		p_buf.sem_num = 1;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		// semwait(2);
		p_buf.sem_num = 2;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);

		printf("idx=%d : msg=%s\n",
				msg_buf->f,
				msg_buf->msg[msg_buf->f]);
		// shared memory의 index 조정
		msg_buf->f = (msg_buf->f + 1) % 10;
		if (!strcmp(msg_buf->msg[msg_buf->f], "quit"))
			break;

		// 세마포 시그널 2개
		// semsig(2);
		p_buf.sem_num = 2;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		// semsig(0);
		p_buf.sem_num = 0;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}

	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID, 0);

	exit(0);
}

