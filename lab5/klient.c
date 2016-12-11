/*
Kamil Pek 231050
11.12.2016
gcc klient.c -o klient.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <string.h>

#define SERWERFIFO "serwerfifo"
#define KLIENTFIFO "/home/majster/klientfifo"

int main(int argc, char *argv[]){
  FILE *fs;
  FILE *fk;
  char *home = getenv("HOME");
  char komunikat[120] = "";
  char readbuf[80] = "";
  int index = 0;

  if(argc != 2){
    printf("Użycie: klientfifo [indeks rekordu bazy]\n");
    exit(1); }

  if((fs = fopen(SERWERFIFO, "w")) == NULL){
    perror("fopen");
    exit(1); }

  strcat(komunikat, argv[1]);
  strcat(komunikat, home);

  do{
    index = index + 1;
  } while(komunikat[index] != '\0');

  fprintf(fs, "%d%s", index, komunikat);
  fclose(fs);

  fk = fopen(KLIENTFIFO, "r");
  fgets(readbuf, 80, fk);
  printf("%s", readbuf);
  fclose(fk);

  return(0);
}
