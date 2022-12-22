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
	fd=open(f, O_WRONLY|O_CREAT, 0600);

	getchar();
	scanf("%c", &loc); 
        while(loc!='E'){
		if (loc=='A'){
			scanf("%d %d %s %lf", &buf.no, &buf.id, buf.name, &buf.score); 
			lseek(fd, buf.no * sizeof(buf), SEEK_SET);
               		write(fd, &buf, sizeof(buf));
		}
		else if (loc=='P'||loc=='N'){
			scanf("%d %s %lf", &buf.id, buf.name, &buf.score); 
			if (loc=='P'){
				buf.no--;
				lseek(fd, -sizeof(buf), SEEK_CUR);
               			write(fd, &buf, sizeof(buf));
			}
			else{
				buf.no++;
               			write(fd, &buf, sizeof(buf));
			}
		}
		getchar();
		scanf("%c", &loc); 
        }

	lseek(fd, 0, SEEK_SET);
	while (read(fd, &buf, sizeof(buf))>0){
		printf("%d %d %s %.2f\n", buf.no, buf.id, buf.name, buf.score);
	}

	return 0;
}
