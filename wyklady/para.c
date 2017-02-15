#include <stdio.h>
main()
{ int n;

   printf("Zaczynamy: \n");
   if (fork() == 0)
      {  sleep(5);
         printf("To ja, proces potomny. Podaj liczbe: ");
         scanf("%5d",&n);
         printf("Potomny: podales liczbe %5d \n",n);
         sleep(5);
         exit(0);
      }   
   else
      {  printf("Teraz to ja, proces macierzysty. Ja tez chce liczbe: \n");
         scanf("%5d",&n);
         printf("Macierzysty: mnie podales %5d \n",n);
         wait();
         sleep(3);
         printf("Konczymy. \n");
      }   
 }
               
         
