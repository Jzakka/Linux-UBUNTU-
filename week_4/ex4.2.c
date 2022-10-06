#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

void printFilename(struct dirent *d){
    struct stat buf;
    char* filename = d->d_name;
    if(filename[0]=='.') return;

    if(stat(filename, &buf) == -1){
        printf("Failed to load file information:%s | %d\n", filename, errno);
        exit(1);
    }
    
    if(S_ISDIR(buf.st_mode)){
        printf("%s*\n", filename);
    }else{
        printf("%s\n", filename);
    }
}

void printAllDirent(DIR *dp, struct dirent *d){
    while (d=readdir(dp)){
        if(d->d_ino!=0){
            printFilename(d);
        }
    }
}

int my_double_ls(const char* name){
    struct dirent *d;
    DIR *dp;

    if((dp=opendir(name))==NULL)
        return -1;

    if(chdir(name)==-1){
        printf("Failed to cd\n");
        exit(1);
    }
    printAllDirent(dp, d);

    rewinddir(dp);

    printAllDirent(dp, d);

    closedir(dp);
}

int main(int argc, char* argv[]){
    if(argc != 2)
        exit(1);

    char* dirname = argv[1];
    my_double_ls(dirname);
}