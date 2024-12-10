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
    char s[300],send[300],vowel[20];
    int num,fd1,fd2,linecnt=0,wordcnt=1,i,k,charcnt=0,a;

    mknod(NAME1,S_IFIFO|0666,0);
    mknod(NAME2,S_IFIFO|0666,0);
    printf("\n1st side connected. Waiting for other side.\n");
    fd1=open(NAME1,O_RDONLY);
    fd2=open(NAME2,O_WRONLY);
    printf("Connection established.\n");

    if(num=read(fd1,s,300)==-1){
        perror("Read something.");
    }

    else{
        s[num]='\0';
        printf("\nRead %d bytes of data.\n",num);

        k=0;
        vowel[0]='\0';

        for(i=0;i<num;i++){
            if((s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]='o'||s[i]=='u')){
                vowel[k]=s[i];
                k++;
            }
            if(s[i]==' ' && s[i+1]!=' '){
                wordcnt++;
            }
            if(s[i]=='.' && (s[i+1]==' ' || s[i+1]=='\0'))
                linecnt++;
            else if(s[i]!='.' && s[i]!=' ')
                charcnt++;
        }
         if(wordcnt!=0 && linecnt==0){
            linecnt++;
         }
        sprintf(send,"Vowel count: %d\nWord count: %d\nCharacter count: %d\nline count: %d\n",k,wordcnt,charcnt,linecnt);
        if(a=write(fd2,send,strlen(send))!=-1){
            printf("Data is written.");
        }
        else{
            printf("error. write.");
        }
        }
        return 0;
    }
   
