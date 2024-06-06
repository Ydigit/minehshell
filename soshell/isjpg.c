#include "shell.h"


int isjpg ( int fileDescriptor )
{
    unsigned char b[4];
    int n = read(fileDescriptor,b,4);
    if ( n < 0){
        perror("erro na leitura");
    }
    lseek(fileDescriptor, 0, SEEK_SET);
    if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0)
        return 1;
    return 0;
}
