/*
Kamil Pek 231050
15.12.2016
gcc serwer.c -o serwer.out -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <string.h>
#include <ctype.h>

#define SERWERFIFO "serwerfifo"
#define KLIENTFIFO "klientfifo"

struct nazwiska{
  int ID;
  char *nazwisko;
};

int main(){
  FILE *fs;
  char readbuf[80] = "", dlugosc[2] = "", index[2] = "", klient[20] = "";
  char sciezka[100] = "";
  char odpowiedz[20] = "nie ma\n", fifo[20] = "/klientfifo";
  int i = 0, j = 0, dx = 0, ix = 0, k = 0, p = 0;

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
    i = j = k = p = dx = ix = 0;
    for(k = 0; k < sizeof(readbuf); k++) readbuf[i] = '\0';
    for(k = 0; k < sizeof(dlugosc); k++) dlugosc[i] = '\0';
    for(k = 0; k < sizeof(index); k++) index[i] = '\0';
    for(k = 0; k < sizeof(klient); k++) klient[i] = '\0';
    for(k = 0; k < sizeof(sciezka); k++) sciezka[i] = '\0';
    strcpy(odpowiedz, "nie ma\n");

    fs = fopen(SERWERFIFO, "r");
    fgets(readbuf, 80, fs);
    fclose(fs);

    // pobieranie dlugosci komunikatu
    dlugosc[0] = readbuf[0];
    dlugosc[1] = readbuf[1];
    sscanf(dlugosc, "%d", &dx);
    dx = dx + 2;

    // ustalanie dlugosci podanej liczby
    while(readbuf[p] != '/') p++;

    // pobieranie indeksu
    if(isdigit(readbuf[3])) {
      index[0] = readbuf[2];
      index[1] = readbuf[3]; }
    else{
      index[0] = readbuf[2];
      index[1] = '\0'; }
    sscanf(index, "%d", &ix);
    ix = ix - 1;
    if(isdigit(readbuf[4])) ix = 22;

    // sprawdzanie indeksu
    if(ix < 20) sscanf(baza[ix].nazwisko, "%s\n", odpowiedz);
    if(ix > 20) strcpy(odpowiedz, "nie ma\n");
    if(ix < 0) strcpy(odpowiedz, "nie ma\n");

    // pobieranie sciezki home klienta
    for(i = p; i < dx; i++){
      klient[j] = readbuf[i];
      j++; }

    // montowanie sciezki do fifo
    strcpy(sciezka, klient);
    strcat(sciezka, fifo);

    // otwieranie fifo u klienta
    fk = fopen(sciezka, "w");
    fprintf(fk, "%s\n", odpowiedz);
    fclose(fk);

    printf("Wysłano odpowiedz do: %s\t %d \n", sciezka, p);
  }
  return(0);
}
