#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

  int bufor = open("bufor.txt", O_RDWR);
  if(bufor < 0){
    printf("Nie mozna otworzyc bufora.\n"); }
  else{
    char slowo[1000] = "";
    char tresc[1000] = "";
    while(1){
      read(bufor, slowo, 256);
      int n = sizeof(slowo);
      printf("%i\n", n);
      printf("%s \n", slowo);
      printf("Podaj tresc wiadomosci.\n");
      scanf("%s", tresc);
      write(bufor, "Serwer pisze: ", 14);
      write(bufor, tresc, 256);
      write(bufor, "\n", 2);
      unlink("lockfile");
    }
    printf("\n");
    close(bufor);
  }
}
