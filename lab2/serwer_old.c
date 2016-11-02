#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

  FILE *buforo  = fopen("bufor.txt", "r");
  if(buforo){
    char slowo[100];
    char c;
    while((c = fscanf(buforo, "%s", slowo)) != EOF){
      printf("%s ", slowo); }
    printf("\n");
    fclose(buforo); }
  else printf("Nie mozna odczytac zawartosci bufora.\n");
  system("/bin/rm -f lockfile");

}
