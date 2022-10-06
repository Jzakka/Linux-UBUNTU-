#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>

int my_double_ls(const char* name, int skip){
    struct dirent *d;
    DIR *dp;

    if((dp=opendir(name))==NULL)
        return -1;

    while (d=readdir(dp)){
        if(d->d_ino!=0){
            if(skip==1 && d->d_name[0]== '.') continue;
            printf("%s\n", d->d_name);
        }
    }

    rewinddir(dp);

    while (d=readdir(dp)){
       if(d->d_ino!=0){
            if(skip==1 && d->d_name[0]== '.') continue;
            printf("%s\n", d->d_name);
        }
    }
    closedir(dp);
}

int main(int argc, char* argv[]){
    if(argc != 3)
        exit(1);

    char* dirname = argv[1];
    int skip = argv[2][0]-'0';
    my_double_ls(dirname, skip);
}