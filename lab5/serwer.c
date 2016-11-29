/*
Kamil Pek 231050
29.11.2016
gcc serwer.c -o serwer.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>

#define SERWERFIFO "serwerfifo"

struct nazwiska{
  int ID;
  char nazwaisko[20];
};

struct nazwiska ludzie[20], bufs;

int main(){
  FILE *fp;
  char readbuf[80];
  // char sample[20] = "test";

  while(1){
    fp = fopen(SERWERFIFO, "r");
    fgets(readbuf, 80, fp);
    // if(readbuf == sample){
    //   printf("jest lol\n");
    // }
    // printf("%s ", sample);
    printf("%s\n", readbuf);
    fclose(fp);
  }
  return(0);
}
