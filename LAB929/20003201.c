void cat_m(char **res){
        char buf[512];
        int fd, n;

        fd=open(res[1], O_RDONLY);
	if (fd==-1) 
		return;
        while((n=read(fd, buf, 512))>0){
                write(1, buf, n);
        }
}

void cd_m(char **res){
	chdir(res[1]);
}

void cp_m(char **res){
	char buf[512];
	int fd1, fd2, n;
	struct stat s;

	fd1=open(res[1], O_RDONLY);
	if (fd1==-1) return;

	stat(res[1], &s);

	fd2=open(res[2], O_WRONLY|O_CREAT|O_TRUNC, s.st_mode&0777);
        while((n=read(fd1, buf, 512))>0){
                write(fd2, buf, n);
        }
}

void ls_m(char **res){
        char f[512];
        int n;
        struct stat s;
        struct dirent *d;
        DIR *dp;

        dp=opendir(".");
        while (d=readdir(dp)){
                if (d->d_name[0]!='.'){
                        stat(d->d_name, &s);
                        if (S_ISREG(s.st_mode))
                                printf("F ");
                        else
                                printf("D ");
                        printf("0%o  ", s.st_mode&0777);
                        printf("%d  ", s.st_nlink);
                        printf("%ld  ", s.st_uid);
                        printf("%ld  ", s.st_gid);
                        printf("%ld  ", s.st_size);
                        strcpy(f, ctime(&s.st_mtime));
                        n=strlen(f);
                        f[n-1]='\0';
                        printf("%s ", f);
                        printf("%s\n", d->d_name);
                }
        }
}

void mkdir_m(char **res){
        mkdir(res[1], 0700);
}

void vi_m(char **res){
        char buf[513];
        int fd, n;

        fd=open(res[1], O_RDWR|O_CREAT, 0600);
        while((n=read(fd, buf, 512))>0){
                write(1, buf, n);
        }
        while((n=read(0, buf, 512))>0){
		buf[n]='\0';
                if (strcmp(buf, "quit\n")==0)
                        break;
                write(fd, buf, n);
        }
}

int main(void){
        char in[100], *res[20]={0};
        char *inst[6]={"cat", "cd", "cp", "ls", "mkdir", "vi"};
        void (*f[6])(char **)={cat_m, cd_m, cp_m, ls_m, mkdir_m, vi_m};
        int i;

        while (1){
		getcwd(in, 100);
               	printf("%s> ", in);

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
