#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    int fd;
    if((fd=open("ex2.3.txt", O_RDONLY)==-1)){
	printf("Cannot open file");
    }
	
    printf("File opened successful-fd: %d\n", fd);

}
