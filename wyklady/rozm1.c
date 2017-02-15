#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define klucz 10

int pamiec, semafory;
char *adres;

void koniec()
   {
      semctl(semafory,0,IPC_RMID,0);
      shmdt(adres);
      shmctl(pamiec,IPC_RMID,0);
      exit(0);
   }   

void odczytaj()
   {
      printf("On powiedzial: %s\n",adres);
      if (strcmp(adres,"KONIEC")==0) koniec();
   }
   
void zapisz()
   {
      printf("Ja mowie: ");
      scanf("%s",adres);
      if (strcmp(adres,"KONIEC")==0) koniec();
   }         

main()
   {
      struct sembuf oper1={0,-1,0},
                    oper2={1,1,0};   
   
      pamiec=shmget(klucz,256,0777|IPC_CREAT);
      semafory=semget(klucz,2,0777|IPC_CREAT);
      adres=shmat(pamiec,0,0);
      semctl(semafory,0,SETVAL,0);
      semctl(semafory,1,SETVAL,1);
      zapisz();
      while (1)
         {
            semop(semafory,&oper1,1);
            odczytaj();
            zapisz();
            semop(semafory,&oper2,1);
         }   
   }       
