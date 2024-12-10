#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#define NAME1 "common_pipe1"
#define NAME2 "common_pipe2"

int main(){
    char s1[300],s2[300];
    int num,fd1,fd2,b;

    mknod(NAME1,S_IFIFO|0666,0);
    mknod(NAME2,S_IFIFO|0666,0);
    printf("\n1st side connected. Waiting for other side.\n");
    fd1=open(NAME1,O_WRONLY);
    fd2=open(NAME2,O_RDONLY);
    printf("Connection established.\nEnter sentences (full stop for new line.)");
    gets(s1);

    if(num=write(fd1,s1,strlen(s1))==-1){
        perror("Write something.");
    }
    else{
        printf("Written %d bytes to pipe1.\n",num);
        b=read(fd2,s2,300);
        s2[b]='\0';
        printf("\n%s\n",s2);
    }
    return 0;
}