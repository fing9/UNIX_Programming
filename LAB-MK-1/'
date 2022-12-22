#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void cat_m(char **res){
        char buf[512]; // buffer 크기는 512 bytes 입니다. 이 부분은 수정하지 마세요. 
        int fd, n;

        if((fd = open(res[1], O_RDONLY)) == -1) {
                return;
        }

        do {
		n = read(fd, buf, 512);
		write(1, buf, n);
        } while(n > 0);
}

void cd_m(char **res){
	
      	// 코드 작성 
      	chdir(res[1]);
}

void cp_m(char **res){
        char buf[512]; // buffer 크기는 512 bytes 입니다. 이 부분은 수정하지 마세요. 
	int fd1, fd2, n;
        struct stat s;
        
      	// 코드 작성 
        fd1 = open(res[1], O_RDONLY);
	
        if(fd1 == -1 || res[1] == 0 || res[2] == 0) {
                return;
        }

        if(fstat(fd1, &s) == -1) {
                return;
        }
	
        fd2 = open(res[2], O_WRONLY|O_CREAT|O_TRUNC, s.st_mode&0777);

        if(fd1 != -1 && fd2 != -1) {
                do {
                        n = read(fd1, buf, 512);
                        write(fd2, buf, n);
                } while(n > 0);
        }

}

void ls_m(char **res){
        char cwd[512], fd, m[2] = ".\0", f[3] = "..\0";
        int ret;
	DIR* dir = NULL;
        struct dirent* dirEntry;
        struct stat s;

      	// 코드 작성 
      	getcwd(cwd, 512);

        if((dir = opendir(cwd)) == NULL) {
                return;
        }

        while((dirEntry = readdir(dir)) != NULL) {
                if(strcmp(dirEntry->d_name, m) && strcmp(dirEntry->d_name, f)) {
			
			ret = stat(dirEntry->d_name, &s);

			if(ret != -1 && !S_ISREG(s.st_mode))
				printf("D ");
			else if(ret != -1)
				printf("F ");
			
                        if(ret != -1) {
                        	printf("0%o  %d  %d  %d  %ld  %s  %s\n", s.st_mode&0777, s.st_nlink, s.st_uid, s.st_gid, s.st_size, ctime(&s.st_mtime), dirEntry->d_name);
			}
                }
        }

}

void mkdir_m(char **res){
      
      	// 코드 작성 
      	mkdir(res[1], 0700);
}


void vi_m(char **res){     
        char buf[512]; // buffer 크기는 512 bytes 입니다. 이 부분은 수정하지 마세요. 
        int fd, n;
      
      	// 코드 작성 
	fd = open(res[1], O_RDWR|O_CREAT|O_APPEND, 0600);
	if((fd = open(res[1], O_RDWR|O_CREAT|O_EXCL, 0600)) == -1) {
		fd = open(res[1], O_RDWR);
		lseek(fd, 0, SEEK_SET);
		do {
			n = read(fd, buf, 512);
			write(1, buf, n);
		} while(n > 0);
	}
	
	do {
		n = read(0, buf, 512);
		write(fd, buf, n);
	} while(!(buf[0] == 'q' && buf[1] == 'u' && buf[2] == 'i' && buf[3] == 't'));
}

int main(void){               
        char in[100], *res[20]={0};
        char *inst[6]={"cat", "cd", "cp", "ls", "mkdir", "vi"};
        void (*f[6])(char **)={cat_m, cd_m, cp_m, ls_m, mkdir_m, vi_m};
        int i;

        while (1){

		// current working directory 이름 출력 (미작성 시 –2점 감점)
		getcwd(in, 100);
		while(in[i]) {
			i++;
		}
		in[i++] = '>';
		in[i++] = ' ';	
		in[i++] = '\0';

		write(1, in, i);		
		
        	gets(in);
		if (in[0]=='\0')
			continue;

		i=0;
          	res[i]=strtok(in, " ");
		while (res[i]){
			i++;
			res[i]=strtok(NULL, " ");
		}

        	if (strcmp(res[0], "exit")==0)
        	         exit(0);

        	for (i=0;i<6;i++){
        	         if (!strcmp(res[0], inst[i])){
        		         f[i](res);
        		         break;
			}
        	}
	}

        return 0;
}
