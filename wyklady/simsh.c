#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define klucz 10

int pamiec,wybor;
char *adres;

void koniec()
   {
      shmdt(adres);
      shmctl(pamiec,IPC_RMID,0);
      exit(0);
   }   

void odczyt()
   {
      printf("Jest zapisane: %s\n",adres);
   }
   
void zapis()
   {
      printf("Podaj lancuch: ");
      scanf("%s",adres);
   }         

main()
   {
      pamiec=shmget(klucz,256,0700|IPC_CREAT);
      adres=shmat(pamiec,0,0);
      for (;;)
         {
            printf("M E N U :\n");
            printf("\n");
            printf("0 - odczyt\n");
            printf("1 - zapis\n");
            printf("2 - koniec\n");
            printf("\n");
            printf("Co wybierasz ? ");
            scanf("%d",&wybor);
            switch(wybor)
               {
                  case 0: odczyt(); break;
                  case 1: zapis(); break;
                  case 2: koniec(); break;
                  default: printf("Nie ma takiej opcji ! \n"); break;
               }
         }         
   }
