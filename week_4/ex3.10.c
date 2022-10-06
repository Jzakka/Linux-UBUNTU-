// 파일이 수정됐는지 주기적으로 확인하고
// 수정되었을 때 표준출력으로 파일 출력

#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFSIZE 4096

char buffer[BUFFSIZE];

struct stat sb;
void printFile(const char* name){
    int fd = open(name, O_RDWR);
    int nread;
    int nwrite;
    while ((nread = read(fd, buffer, BUFFSIZE)) != -1){
        if((nwrite = write(1, buffer, nread))<nread){
            printf("write error!\n");
            exit(1);
        }
    }
    if(nread==-1) {
        printf("read error!\n");
        exit(1);
    }
}

void cmp (const char* name, time_t last){
    // struct stat 의 데이터를 얻는 데에 실패했거나 || 최근 수정일이 최근이 아닐 때
    if(stat(name, &sb)==-1){
        perror("Failed to load file information\n");
        exit(1);
    }
    if(sb.st_mtime != last){
        last = sb.st_mtime;
        printFile(name);
    }
}

int main(int argc, char* argv[]){
    int j;
    time_t lastTime;

    if(argc!=2){
        perror("USAGE: [PATH]/slowwatch [FILENAME]\n");
        exit(1);
    }

    char* filename = argv[1];

    if(stat(filename, &sb)==-1){
        perror("Failed to load file information\n");
        exit(1);
    }
    lastTime = sb.st_mtime;

    while (1)
    {
        cmp(filename, lastTime);
        sleep(10);
    }
}