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

int rozmiar(char komunikat[120]){
  int index = 0;
  int i = 0;
  // int dlg = 0;
  // dlg = sizeof(komunikat);
  do{
    index = index + 1;
  } while(komunikat[i] != '\0');
  printf("%d\t", index);
  return index;
}

int main(int argc, char *argv[]){
  FILE *fp;
  char *home = getenv("HOME");
  int dlugosc = 0;

  if(argc != 2){
    printf("Użycie: klientfifo [indeks rekordu bazy]\n");
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

  dlugosc = sizeof(komunikat) / sizeof(komunikat[0]);
  // dlugosc = rozmiar(komunikat);

  fputs(komunikat, fp);
  printf("%d\t", dlugosc);
  printf("%c\n", komunikat[100]);

  fclose(fp);
  return(0);
}
