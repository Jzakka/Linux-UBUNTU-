#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("USAGE: ex2.7.out 2 [filename]");
        exit(0);
    }
    char *filename = argv[1];
    int infile, outfile;

    if ((infile = open(filename, O_RDONLY)) == -1) {
        printf("InputFile could not be opened successful");
        exit(0);
    }

    if ((outfile = (open("copiedFile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644))) == -1) {
        printf("OutputFile could not be opened successful");
        close(infile);
        exit(0);
    }

    ssize_t readByte;
    char buff[BUFF_SIZE];

    while ((readByte = read(infile, buff, BUFF_SIZE) > 0)) {
        if (write(outfile, buff, BUFF_SIZE) < readByte) {
            close(outfile);
            close(infile);
            printf("write error!");
        }
    }

    close(outfile);
    close(infile);

    if (readByte == -1) printf("read error!");
    else printf("File Copied successful!\n %s->copiedFile.txt", filename);

    return 0;
}
