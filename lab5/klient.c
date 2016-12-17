/*
Kamil Pek 231050
17.12.2016
gcc klient.c -o klient.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <string.h>
#include <fcntl.h>

#define SERWERFIFO "/home/studinf/kpek/serwerfifo"
#define KLIENTFIFO "/home/studinf/kpek/klientfifo"

int main(int argc, char *argv[]){
  // FILE *fs;
  int fs = 0;
  FILE *fk;
  char *home = getenv("HOME");
  char msg[200] = "";
  char komunikat[120] = "";
  char readbuf[80] = "";
  int index = 0;

  if(argc != 2){
    printf("Użycie: klientfifo [indeks rekordu bazy]\n");
    exit(1); }

  fs = open(SERWERFIFO, O_WRONLY);
  if(fs == -1) printf("Blad otwarcia\n");

  strcat(komunikat, argv[1]);
  strcat(komunikat, home);

  do{
    index = index + 1;
  } while(komunikat[index] != '\0');

  sprintf(msg, "%d%s", index, komunikat);
  write(fs, msg, strlen(msg)+1);
  close(fs);

  fk = fopen(KLIENTFIFO, "r");
  fgets(readbuf, 80, fk);
  printf("%s\n", readbuf);
  fclose(fk);

  return(0);
}
