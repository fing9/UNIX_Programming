#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//--system call--
//
//fd = open("filename", O_WRONLY|O_CREAT|O_TRUNC, 0644)  (실행실패시 -1 반환)
//O_RDONLY|O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_TRUNC| O_APPEND  (파일포인터 맨 뒤로)
//read(fd, &buffer, datasize)  더이상 읽을게 없으면 0리턴, 실제 읽힌 바이트 수 반환, 실패 시 -1
//write(fd, &buffer, datasize)  쓰기 전에 꽉 차면 -1 리턴
//creat("filename", mode)  무조건 write only로 오픈, 기존 파일은 0으로 오픈(지우고 오픈
//close(filedes)
//
//lseek(fd, 얼마마큼갈래, SEEK_SET|SEEK_CUR|SEEK_END)  시작|현재|끝 지점으로 이동 , 이동 실패시 -1
//
//파일삭제 remove("filename")
//
//
//----------------------------------------------------------------------
//pipe란?
//1. 표준 출력한 내용들이 전부 outfile에 저장된다.
//
// ./a.out < infile
// ./a.out > outfile
// ./a.out < infile > outfile
//
// ./a.out | ./a.out2      a.out1의 표준 출력이 a.out2의 표준 입력으로
//-----------------------------------------------------------------------
// fstat(fd, struct stat &buf)   이러면 buf에 파일 정보가 저장됨 (먼저 struct stat 변수를 선언해야겠다)
// st_dev, st_ino : 논리적 장치 번호와 inode 번호(시스템 상에서 이 파일의 id)
// st_mode : permission mode &0777해야지 제대로된 값이 나옴 why? 8진수이기 때문
// st_nlink : link의 수
// st_uid, st_gid : user의 uid와 gid
// st_rdev : file이 장치인 경우만 사용
// st_size : 논리적 크기
// st_atime, st_mtime, st_ctime : file의 최근 access time, update time, stat 구조의 update time
// st_blksize : I/O block 크기
// st_blocks : 파일에 할당된 block의 수
// ----------------------------------------------------------------------
// access("filename", R_OK|W_OK|X_OK|F_OK)    읽기가능, 쓰기가능, 실행가능, 파일존재,   리턴값은 0 or -1
//
// fchmod(fd, 0644)
//
// link("파일", "새로운 이름")
//
// getcwd("filename", 크기)  경로받기
// 
// chdir("filename")  해당하는 디렉토리로 이동
//
// ----------------------------------------------------------------------
// 
// 복사 y, y5
// 붙여넣기 p
// 되돌리기 u
// 지우기 d
// 


//test2 source code
int main(void) {
	
	
	return 0;
}

