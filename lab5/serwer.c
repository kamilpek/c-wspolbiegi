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
#include <string.h>

#define SERWERFIFO "serwerfifo"
#define KLIENTFIFO "klientfifo"

struct nazwiska{
  int ID;
  char *nazwisko;
};

int main(){
  FILE *fp;
  char readbuf[80];
  char sample[80] = "test";
  int i = 0;

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

  for(i = 1; i < 20; i++){
    baza[i].ID = i;
  }

  // for(i = 0; i < 20; i++){
  //   printf("%d %s\n", baza[i].ID, baza[i].nazwisko);
  // }

  while(1){
    char tresc[2] = "";
    fp = fopen(SERWERFIFO, "r");
    fgets(readbuf, 80, fp);
    if(strcmp(readbuf, sample) == 0){
      printf("test działa\n");
    }
    // printf("%s ", sample);
    strcat(tresc, readbuf);
    // strcat(tresc, readbuf[1]);
    printf("%s\n", tresc);
    fclose(fp);
  }
  return(0);
}
