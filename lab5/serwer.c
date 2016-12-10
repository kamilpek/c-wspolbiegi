/*
Kamil Pek 231050
10.12.2016
gcc serwer.c -o serwer.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <string.h>

#define SERWERFIFO "serwerfifo"
#define KLIENTFIFO "klientfifo"

struct nazwiska{
  int ID;
  char *nazwisko;
};

int main(){
  FILE *fs;
  char readbuf[80] = "", dlugosc[2] = "", index[2] = "", klient[20] = "", sciezka[100] = "";
  int i = 0, j = 0, dx = 0, ix = 0, k = 0;

  struct nazwiska baza[20];
  baza[0].nazwisko = "Nowak";
  baza[1].nazwisko = "Kowalski";
  baza[2].nazwisko = "Wisniewski";
  baza[3].nazwisko = "Wojcik";
  baza[4].nazwisko = "Kowalczyk";
  baza[5].nazwisko = "Kaminski";
  baza[6].nazwisko = "Lewandowski";
  baza[7].nazwisko = "Dabrowski";
  baza[8].nazwisko = "Zielinski";
  baza[9].nazwisko = "Szymanski";
  baza[10].nazwisko = "Wozniak";
  baza[11].nazwisko = "Kozlowski";
  baza[12].nazwisko = "Jankowski";
  baza[13].nazwisko = "Mazur";
  baza[14].nazwisko = "Wojciechowski";
  baza[15].nazwisko = "Kwiatkowski";
  baza[16].nazwisko = "Krawczyk";
  baza[17].nazwisko = "Kaczmarek";
  baza[18].nazwisko = "Piotrowski";
  baza[19].nazwisko = "Grabowski";

  for(k = 1; k < 20; k++) baza[k].ID = k;

  // wyswietlanie wszystkich rekordow bazy danych
  // for(i = 0; i < 20; i++) printf("%d %s\n", baza[i].ID, baza[i].nazwisko);

  while(1){
    FILE *fk;
    i = j = k = dx = ix = 0;
    for(k = 0; k < sizeof(readbuf); k++) readbuf[i] = '\0';
    for(k = 0; k < sizeof(dlugosc); k++) dlugosc[i] = '\0';
    for(k = 0; k < sizeof(index); k++) index[i] = '\0';
    for(k = 0; k < sizeof(klient); k++) klient[i] = '\0';
    for(k = 0; k < sizeof(sciezka); k++) sciezka[i] = '\0';

    fs = fopen(SERWERFIFO, "r");
    fgets(readbuf, 80, fs);
    fclose(fs);

    // pobieranie dlugosci komunikatu
    dlugosc[0] = readbuf[0];
    dlugosc[1] = readbuf[1];
    sscanf(dlugosc, "%d", &dx);
    dx = dx + 2;

    // pobieranie indeksu
    if(readbuf[3] != '/') {
      index[0] = readbuf[2];
      index[1] = readbuf[3]; }
    else index[0] = readbuf[2];
    sscanf(index, "%d", &ix);
    ix = ix - 1;

    // pobieranie sciezki home klienta
    if(readbuf[3] != '/') {
      for(i = 4; i < dx; i++){
        klient[j] = readbuf[i];
        j++; } }
    else {
      for(i = 3; i < dx; i++){
        klient[j] = readbuf[i];
        j++; } }

    // otwieranie fifo u klienta
    fk = fopen(KLIENTFIFO, "w");
    fprintf(fk, "%s\n", baza[ix].nazwisko);
    fclose(fk);

    // printf("%s\n", sciezka);
    // printf("%s\n", baza[ix].nazwisko);
  }
  return(0);
}
