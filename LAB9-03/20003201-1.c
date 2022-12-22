#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(void){
	int n;
	n = access("data1", F_OK);
	
	if(n == 0) {
		printf("File exist\n");
		n = access("data1", R_OK);
		if(n == 0) printf("Read Ok\n");
		else printf("Read Not Ok\n");
		
		n = access("data1", W_OK);
		if(n == 0) printf("Write Ok\n");
		else printf("Write Not Ok\n");
	
	}
	else {
		printf("File dosen't exist\n");	
	}
	
	return 0;
}
