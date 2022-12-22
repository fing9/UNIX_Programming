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
#define R 4
#define B 10

struct databuf1{
        int s_id;
        char msg[512];
};

struct databuf2{
        int index; // 다음번에 몇 번 인덱스에서 일하는가
        int members[R]; // 통신에 참여하고있는 인원들 표시
        struct databuf1 buf[B]; //
};

union semun{
        int val;
        struct semid_ds *buf;
        ushort *array;
};

void sem_wait(int semid, int semidx){
        struct sembuf p_buf={semidx, -1, 0};

        if (semop(semid, &p_buf, 1)==-1)
		printf("semwait fails...\n");
}

void sem_signal(int semid, int semidx){
        struct sembuf p_buf={semidx, 1, 0};

        if (semop(semid, &p_buf, 1)==-1)
		printf("semsignal fails...\n");
}

void do_reader(int id, int rindex, struct databuf2 *buf, int semid){
        int i;

        for (i=rindex; ; i=buf->index){
                // semaphore를 이용한 동기화
				// 세마포 웨이트
				sem_wait(semid, 2*(id-1)+1);
                if (buf->buf[i].s_id!=id){
                        printf("[sender=%d & msg#=%d] %s\n", buf->buf[i].s_id, i, buf->buf[i].msg);
                }
                // semaphore를 이용한 동기화
				// 세마포 시그널 (웨이트와 시그널이 서로 다름)
				sem_signal(semid, 2*(id-1));
                if (strcmp(buf->buf[i].msg, "talk_quit")==0 && buf->buf[i].s_id==id)
                        break;
        }

        exit(0);
}

void do_writer(int id, struct databuf2 *buf, int semid){
        char temp[512];
        int i, flag=0, cnum;

        for ( ; ; ){
                scanf("%s", temp);
		cnum=0;

		// semaphore를 이용한 동기화 1 
        // semaphore를 이용한 동기화 2
		for (i=1;i<=R;i++) {
			if (buf->members[i-1] == 1)
				sem_wait(semid, 2*(i-1));
		}
		sem_wait(semid, 2*R);

        strcpy(buf->buf[buf->index].msg, temp);
        buf->buf[buf->index].s_id=id;
        buf->index = (buf->index+1)%B;
		if (cnum==1)
			printf("id=%d, talkers=%d, msg#=%d...\n", id, cnum, buf->index);

		// semaphore를 이용한 동기화 1 
        // semaphore를 이용한 동기화 2
		sem_signal(semid, 2*R);
		for (i=1;i<=R;i++) {
			if (buf->members[i-1] == 1)
				sem_signal(semid, 2*(i-1)+1);
		}

		if (strcmp(temp, "talk_quit")==0)
			break;
        }

	exit(0);
}

int main(int argc, char** argv){
    int id, semid, shmid, i, j, flag, cnum, rindex;
	// {1wr, 1rd, 2wr, 2rd, 3wr, 3rd, 4wr, 4rd, 상호배제}
    ushort init[2*R+1]={10, 0, 10, 0, 10, 0, 10, 0, 1}; // 세마포는 2*R + 1개가 필요하다.
	key_t key1, key2;
	pid_t pid[2];
    union semun arg;
    struct databuf2 *buf;

	key1=ftok("key", 12);
    // semaphore 생성 및 초기화
	semid = semget(key1, 2*R+1, 0600|IPC_CREAT|IPC_EXCL);
	if(semid == -1) {
		semid = semget(key1, 2*R+1, 0);
	}
	else {
		arg.array = init;
		semctl(semid, 0, SETALL, arg);
	}											

	key2=ftok("key", 23);
    // shared memory 생성 및 부착
	shmid = shmget(key2, sizeof(struct databuf2), 0600|IPC_CREAT|IPC_EXCL);
	if(shmid == -1) {
		shmid = shmget(key2, sizeof(struct databuf2), 0);
	}
	buf = shmat(shmid, 0, 0);

	
	id=atoi(argv[1]); // 1 2 3 4로 아이디가 들어온다고 가정

    // semaphore를 이용한 동기화
	sem_wait(semid, 2*R);
	if (buf->members[id-1]==0){  // ID 번호가 이미 있으면 접족못하게 하려는거임
        buf->members[id-1]=1;
		// 사용할 semaphore 초기값 지정
		arg.val = 10;
		semctl(semid, 2*(id-1), SETVAL, arg);
		arg.val = 0;
		semctl(semid, 2*(id-1)+1, SETVAL, arg);
	}
	else
		id=-1;
	cnum=0;
	for (i=0; i<R; i++){ // 대화에 참여중인 인원수 체크
		if (buf->members[i]==1)
			cnum++;
	}
	// 읽기 시작 위치 확인| 몇 번부터 읽으면 되는지 확인
	rindex = buf->index;
	// semaphore를 이용한 동기화
	sem_signal(semid, 2*R);

	if (id==-1)
		return 0;
	printf("id=%d, talkers=%d, msg#=%d...\n", id, cnum, rindex);

	for (i=0; i<2; i++){
		pid[i]=fork();
        if (pid[i]==0 && i==0)
            do_reader(id, rindex, buf, semid);
		else if (pid[i]==0 && i==1)
        	do_writer(id, buf, semid);
	}

	for (i=0; i<2; i++){
        wait(0);
	}

    // semaphore를 이용한 동기화
	sem_wait(semid, 2*R);
    buf->members[id-1]=0;
	for (i=0;i<R;i++) {
		if(buf->members[i]==1)
			cnum++;
	}
	sem_signal(semid, 2*R);

	if(cnum == 0) {
		shmctl(shmid, IPC_RMID, 0);
		semctl(semid, 0, IPC_RMID, 0);
	}

    exit(0);
}
