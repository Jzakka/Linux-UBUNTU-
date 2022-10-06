#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int lsoct(char* permission);
int strToOct(char* octStr);

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("USAGE: [PATH/setperm] [FILENAME] [PERMISSION]");
        exit(0);
    }

    char* filename = argv[1];
    char* permission = argv[2];

    if (permission[0] >= '0' && permission[0] <= '9'){
        //8진수 형태일 때
        if(chmod(filename, (mode_t)strToOct(permission))==-1){
            printf("Failed to set permission\n");
            exit(1);
        }
    }
       
    else{
        //ls 스타일일 때
        if(chmod(filename, (mode_t)lsoct(permission))==-1){
            printf("Failed to set permission\n");
            exit(1);
        }
    }
        
    printf("Permission changed successfully!\n");
    
    return 0;
}

int lsoct(char *permission)
{
    int oct = 0;
    if (permission[0] == 'r')
        oct += 0400;
    if (permission[1] == 'w')
        oct += 0200;
    if (permission[2] == 'x')
        oct += 0100;

    if (permission[3] == 'r')
        oct += 0040;
    if (permission[4] == 'w')
        oct += 0020;
    if (permission[5] == 'x')
        oct += 0010;

    if (permission[6] == 'r')
        oct += 0004;
    if (permission[7] == 'w')
        oct += 0002;
    if (permission[8] == 'x')
        oct += 0001;
    return oct;
}

int strToOct(char* octStr){
    int oct = 0;
    oct += (octStr[1]-'0')* 64;
    oct += (octStr[2]-'0')* 8;
    oct += (octStr[3]-'0');

    return oct;
}

