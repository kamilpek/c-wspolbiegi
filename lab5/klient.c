/*
Kamil Pek 231050
06.12.2016
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
  // FILE *fs;
  char *home = getenv("HOME");
  char komunikat[120] = "";
  char readbuf[80] = "";
  int index = 0;

  if(argc != 2){
    printf("Użycie: klientfifo [indeks rekordu bazy]\n");
    exit(1); }

  if((fp = fopen(SERWERFIFO, "w")) == NULL){
    perror("fopen");
    exit(1); }

  strcat(komunikat, argv[1]);
  strcat(komunikat, home);

  do{
    index = index + 1;
  } while(komunikat[index] != '\0');

  fprintf(fp, "%d%s", index, komunikat);

  // fs = fopen(SERWERFIFO, "r");
  // fgets(readbuf, 80, fs);
  // printf("%s", readbuf);

  fclose(fp);
  // fclose(fs);
  return(0);
}
