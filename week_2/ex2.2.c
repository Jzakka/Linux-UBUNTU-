#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    int fd;
    if((fd = open("ex2.2.txt", O_RDWR |  O_CREAT, 0644))==-1){
	    printf("File could not open\n");
	   exit(0);
	   }
    printf("file opened successful- fd: %d\n",fd);
}
