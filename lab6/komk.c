#include <stdio.h>
#include <stdlib.h>
#include <linux/msg.h>
#include <linux/ipc.h>

#define klucz 10

struct komunikat
   {
      long typ;
      char dane[256];
   };
   
main()
   {
      struct komunikat kom;
      int kolejka, *wsk;
      long ident;  
      
      kolejka=msgget(klucz,0777);
      ident=getpid();
      wsk=(int*) kom.dane;
      *wsk=5;
      kom.typ=ident;
      msgsnd(kolejka,&kom,sizeof(int),0);
      printf("klient %5d wyslalem %5d\n", ident, *wsk);
      msgrcv(kolejka,&kom,sizeof(int),ident,0);
      printf("klient %5d otrzymalem %5d\n", ident, *wsk);
   }       