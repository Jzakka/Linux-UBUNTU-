#include <stdio.h>
#include <stdlib.h>

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

void octToPerm(int pos, int per, char *result)
{
    switch (per)
    {
    case 7:
        result[pos] = 'r';
        result[pos + 1] = 'w';
        result[pos + 2] = 'x';
        break;
    case 6:
        result[pos] = 'r';
        result[pos + 1] = 'w';
        result[pos + 2] = '-';
        break;
    case 5:
        result[pos] = 'r';
        result[pos + 1] = '-';
        result[pos + 2] = 'x';
        break;
    case 4:
        result[pos] = 'r';
        result[pos + 1] = '-';
        result[pos + 2] = '-';
        break;
    case 3:
        result[pos] = '-';
        result[pos + 1] = 'w';
        result[pos + 2] = 'x';
        break;
    case 2:
        result[pos] = '-';
        result[pos + 1] = 'w';
        result[pos + 2] = '-';
        break;
    case 1:
        result[pos] = '-';
        result[pos + 1] = '-';
        result[pos + 2] = 'x';
        break;
    case 0:
        result[pos] = '-';
        result[pos + 1] = '-';
        result[pos + 2] = '-';
        break;
    default:
        break;
    }
}

int strToOct(char* octStr){
    int oct = 0;
    oct += (octStr[1]-'0')* 64;
    oct += (octStr[2]-'0')* 8;
    oct += (octStr[3]-'0');

    return oct;
}

char *octls(char* octStr)
{
    // permission이 4자리의 8진수 숫자로 들어온다고 가정
    int oct = strToOct(octStr);
    
    char *permission = (char *)malloc(10 * sizeof(char));
    int userPerm = oct / (8 * 8);
    int groupPerm = oct % (8 * 8) / 8;
    int otherPerm = oct % 8;

    octToPerm(0, userPerm, permission);
    octToPerm(3, groupPerm, permission);
    octToPerm(6, otherPerm, permission);

    return permission;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(1);

    char *permission = argv[1];

    if (permission[0] >= '0' && permission[0] <= '9')
        printf("%s\n", octls(permission));
    else
        printf("%#o\n", lsoct(permission));

    return 0;
}
