/*
Kamil Pek 231050
29.11.2016
gcc klient.c -o klient.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>

#define SERWERFIFO "serwerfifo"
#define KLIENTFIFO "klientfifo"

int main(int argc, char *argv[]){
  FILE *fp;

  if(argc != 2){
    printf("Użycie: klientfifo [łanćuch]\n");
    exit(1);
  }

  if((fp = fopen(SERWERFIFO, "w")) == NULL){
    perror("fopen");
    exit(1);
  }

  fputs(argv[1], fp);

  fclose(fp);
  return(0);
}
