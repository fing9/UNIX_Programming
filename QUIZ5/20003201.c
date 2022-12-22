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

struct q_entry{
    long mtype;
	int snum;
    int cnum;
    int s_id;
    char msg[512];
};

struct q_entry cmessage(int mtype, int snum, int cnum);
struct q_entry nmessage(int mtype, int s_id, char *str);

void do_writer(int qid, int id){
	char temp[512];
    int i, cnum, index;
    struct q_entry msg1, msg2;

    while(1){
        scanf("%s", temp);

		// (3) message를 보내기 위한 준비
		msgrcv(qid, &msg1, sizeof(msg1)-sizeof(long), 123456789, 0);
		msg1=cmessage(123456789, msg1.snum+1, msg1.cnum);
		index = msg1.snum;
		msgsnd(qid, &msg1, sizeof(msg1)-sizeof(long), 0);
		cnum = msg1.cnum;

		msg2=nmessage(index, id, temp);
		// (3) message 보내기
		for(i=0;i<msg1.cnum;i++) {
			msgsnd(qid, &msg2, sizeof(msg2)-sizeof(long), 0);
		}

		if (cnum==1)
			printf("id=%d, talkers=%d, msg#=%d ...\n", id, msg1.cnum, msg1.snum);

        if (strcmp(temp, "talk_quit")==0)
            break;
    }

    exit(0);
}

void do_reader(int qid, int id, int index){
    struct q_entry msg;

    while(1){
		// (4) message 받기
		msgrcv(qid, &msg, sizeof(msg)-sizeof(long), index, 0);

        if (msg.s_id!=id){
                printf("[sender=%d & msg#=%d] %s\n", msg.s_id, msg.mtype, msg.msg);
        }
		else if (msg.s_id==id && strcmp(msg.msg, "talk_quit")==0)
			break;
		// (4) 다음 message를 받기 위한 준비
		index++;
    }

	exit(0);
}

int main(int argc, char** argv){
    int i, qid, id, index;
	pid_t pid[2];
    key_t key;
    struct q_entry msg1, msg2;

    key=ftok("key", 96);
    if ((qid=msgget(key, 0600|IPC_CREAT|IPC_EXCL))>0){
		// (1) message를 순차적으로 주고 받기 위한 준비 2line
		msg2 = cmessage(123456789, 1, 0); // type, snum, cnum
		msgsnd(qid, &msg2, sizeof(msg2)-sizeof(long), 0);
	}
    else{
        qid=msgget(key, 0);
    }

	id=atoi(argv[1]);
	// snum: msg number, cnum: talkers total number
	// (2) 새롭게 talk에 참여 했음을 알리고, 첫번째 message를 받기 위한 준비 4line
	msgrcv(qid, &msg1, sizeof(msg1)-sizeof(long), 123456789, 0);
	msg1 = cmessage(123456789, msg1.snum, msg1.cnum+1);
	msgsnd(qid, &msg1, sizeof(msg1)-sizeof(long), 0);
	index = msg1.snum+1;
	
	printf("id=%d, talkers=%d, msg#=%d ...\n", id, msg1.cnum, msg1.snum);

	for (i=0; i<2; i++){
		pid[i]=fork();
		if (pid[i]==0&&i==0)
            do_reader(qid, id, index);
		else if (pid[i]==0&&i==1)
            do_writer(qid, id);
	}

	for (i=0; i<2; i++){
        	wait(0);
	}

	msgrcv(qid, &msg1, sizeof(msg1)-sizeof(long), 123456789, 0);
	if(msg1.cnum == 1) {
		msgctl(qid, IPC_RMID, (struct msqid_ds *) NULL);
		exit(0);
	}
	else {
		msg1 = cmessage(123456789, msg1.snum, msg1.cnum-1);
	}
	msgsnd(qid, &msg1, sizeof(msg1)-sizeof(long), 0);

	exit(0);
}

struct q_entry cmessage(int mtype, int snum, int cnum){
	struct q_entry msg;
	
	msg.mtype=mtype;
	msg.snum=snum;
	msg.cnum=cnum;
	msg.s_id=0;
	strcpy(msg.msg, "");

	return msg;
}

struct q_entry nmessage(int mtype, int s_id, char *str){
	struct q_entry msg;
	
	msg.mtype=mtype;
	msg.snum=0;
	msg.cnum=0;
	msg.s_id=s_id;
	strcpy(msg.msg, str);

	return msg;
}

// msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);
