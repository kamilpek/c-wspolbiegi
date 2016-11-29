/*
Kamil Pek 231050
29.11.2016
gcc klient.c -o klient.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>

#define KLIENTFIFO "klientfifo"

int main(){
  FILE *fp;
  char readbuf[80];

  while(1){
    fp = fopen(KLIENTFIFO, "r");
    fgets(readbuf, 80, fp);
    printf("%s\n", readbuf);
    fclose(fp);
  }
  return(0);
}
