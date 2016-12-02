/*
Kamil Pek 231050
29.11.2016
gcc klient.c -o klient.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERWERFIFO "serwerfifo"
#define KLIENTFIFO "klientfifo"

int main(int argc, char *argv[]){
  FILE *fp;
  char *home = getenv("HOME");
  int dlugosc = 0;

  if(argc != 2){
    printf("Użycie: klientfifo [łanćuch]\n");
    exit(1);
  }

  if((fp = fopen(SERWERFIFO, "w")) == NULL){
    perror("fopen");
    exit(1);
  }

  char komunikat[120] = "";
  strcat(komunikat, home);
  strcat(komunikat, " ");
  strcat(komunikat, argv[1]);

  // dlugosc = sizeof(komunikat);

  // write(fp, "elo", 3);
  fputs(komunikat, fp);
  printf("%d\n", dlugosc);

  fclose(fp);
  return(0);
}
