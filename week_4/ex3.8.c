#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        perror("USAGE: rm [FILENAME]\n");
        exit(1);
    }
        
    char* filename = argv[1];

    if(access(filename, W_OK)==-1){
        perror("No permission!You can't remove the file.\n");
        exit(1);
    }

    if(unlink(filename)==-1){
        perror("Unlink failed.\n");
        exit(1);
    }

    printf("%s was removed successful!", argv[1]);
}