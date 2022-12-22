#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int i, k1, k2;
	k1=atoi(argv[1]);
	k2=atoi(argv[2]);
	for (i=k1; i<k2; i++){
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}
