#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct stud{                // 구조체 멤버와 데이터 타입을 변경하지 마시오. 
	int no, id;
	char name[20];
	double score;
};

int main(void){
	char f[100], loc;
	int fd, n;
	struct stud buf;

	scanf("%s", f);        // 입력된 데이터를 저장할 파일 이름 입력
	fd=open(f, O_RDWR|O_CREAT|O_TRUNC, 0644); // 파일 open

	getchar();
	scanf("%c", &loc);     // 각 데이터의 첫 번째 문자 입력
        while(loc!='E'){
		char end = '\n';
		if (loc=='A'){
			scanf("%d %d %s %lf", &buf.no, &buf.id, buf.name, &buf.score);
			lseek(fd, buf.no*(sizeof(buf)+1), SEEK_SET);
			write(fd, &buf, sizeof(buf));
			write(fd, &end, 1);
			// 순번, 학번, 이름, 성적을 입력받아, 파일의 지정된 위치에 저장
		}
		else if (loc=='P'||loc=='N'){
			scanf("%d %s %lf", &buf.id, buf.name, &buf.score);
			if (loc=='P'){
				lseek(fd, -(sizeof(buf)+1), SEEK_CUR);
				read(fd, &buf.id, sizeof(int));
				if(buf.id != 0)
					buf.id -= 1;
				lseek(fd, -(sizeof(buf)+1) - sizeof(int), SEEK_CUR);
				write(fd, &buf, sizeof(buf));
				write(fd, &end, 1);
				 // 마지막으로 입력된 데이터의 바로 앞에 저장
			}
			else{
				lseek(fd, -(sizeof(buf)+1), SEEK_CUR);
				read(fd, &buf.id, sizeof(int));
				buf.id += 1;
				lseek(fd, sizeof(buf)+1 - sizeof(int), SEEK_CUR);
				write(fd, &buf, sizeof(buf));
				write(fd, &end, 1);
				 // 마지막으로 입력된 데이터의 바로 다음에 저장
			}
		}
		getchar();
		scanf("%c", &loc);     // 각 데이터의 첫 번째 문자 입력
        }

	char buf2[512];
	do{
	n = lseek(fd, 0, SEEK_SET);
	read(fd, &buf2, 512);
	printf("%s", buf2);
	} while(n > 0);
	 // 파일을 읽어서 지금까지 저장된 내용 출력

	return 0;
}
