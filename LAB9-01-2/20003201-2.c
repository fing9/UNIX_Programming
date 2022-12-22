#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	char n1[50], n2[50], buf[512], in;
	int i, fd1, fd2, n;

	scanf("%s", n1);
	scanf("%s", n2);

	fd1 = open(n1, O_RDONLY); //파일이 있으면 True, 없으면 FALSE 반환
	if(fd1 == -1) { //파일이 존재하지 않는다면
		printf("%s : No such file...\n", n1);
		return 0;
	}
	
	fd2 = open(n2, O_WRONLY|O_CREAT|O_EXCL, 0644);
	if(fd2 == -1) { //파일이 존재한다면
		printf("%s : File already exists...Do you want to overwrite it?\n", n2);
		getchar();
		in = getchar();
		if(in != 'Y') {
			return 0;
		}
		fd2 = open(n2, O_WRONLY|O_CREAT|O_TRUNC, 0644); //있던 파일을 지우고 오픈
		//fd2 = open(n2, O_WRONLY|O_TRUNC);
	}
	
	//fd1에서 fd2로 복사
	for(i=0;i<sizeof(buf) && buf[0] != EOF;i++) {
		read(fd1, buf, sizeof(char));
		write(fd2, &buf[0], sizeof(char));
	}

	/*
 * do{ 
 * 	i = read(fd1, buf, 512);
 * 	write(fd2, buf, i);
 * }while(i > 0);
 	*/

	
	return 0;

