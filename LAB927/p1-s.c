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

struct stud{
	int no, id;
	char name[20];
	double score;
};

int main(void){
	char f[100], loc;
	int fd, n;
	struct stud buf;

	scanf("%s", f);

	getchar();
	scanf("%c", &loc); 
        while(loc!='E'){
		if (loc=='A'){
			scanf("%d %d %s %lf", &buf.no, &buf.id, buf.name, &buf.score); 
			printf("%d %d %s %.2f\n", buf.no, buf.id, buf.name, buf.score);
		}
		else if (loc=='P'||loc=='N'){
			scanf("%d %s %lf", &buf.id, buf.name, &buf.score); 
			printf("%d %s %.2f\n", buf.id, buf.name, buf.score); 
			if (loc=='P'){
				
			}
			else{
			}
		}
		getchar();
		scanf("%c", &loc); 
        }

	return 0;
}
