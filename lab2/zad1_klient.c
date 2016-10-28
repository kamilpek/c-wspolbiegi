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
      printf("%s\n", slowo); }
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
  FILE *buforz = fopen("bufor.txt", "a");

  czyscbufor();
  fprintf(buforz, "%s", argv[1]);

  printf("Podaj tresc wiadomosci:\n");
  scanf("%s", tekst);
  fprintf(buforz, " pisze: %s\n", tekst);

  fclose(buforz);
  serwer();
  // odczyt();
  return 0;
}
