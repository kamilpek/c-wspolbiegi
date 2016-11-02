#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void odczyt(){
  FILE *buforo  = fopen("bufor.txt", "r");
  if(buforo){
    char slowo[100];
    char c;
    while((c = fscanf(buforo, "%s", slowo)) != EOF){
      printf("%s " , slowo); }
    printf("\n");
    fclose(buforo); }
  else printf("Nie mozna odczytac zawartosci bufora.\n");
}

void serwer(){
  while(open("lockfile", O_CREAT|O_EXCL, 0) == -1){
    printf("Serwer zajety, prosze czekac\n");
    sleep(5); }
}

void czyscbufor(){
  FILE *buforc = fopen("bufor.txt", "w");
  if(buforc){
    char cz[1] = "";
    fprintf(buforc, "%s", cz);
    fclose(buforc); }
}

int main(int argc, char *argv[]){
  char tekst[1000] = "";
  int bufor = open("bufor.txt", O_RDWR);

  czyscbufor();

  printf("Podaj tresc wiadomosci:\n");
  gets(tekst);
  write(bufor, tekst, 1000);

  close(bufor);
  serwer();
  odczyt();
  return 0;
}
