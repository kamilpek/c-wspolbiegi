#include <stdio.h>
main()
{ int childpid,st1,ident;
   printf("Uwaga, wywolujemy potomka.\n");
   sleep(3);
   childpid=fork();
   if (childpid == 0)
         execl("/home/users/jsk/Wyklad7/Simple/potomek","potomek",NULL);
      else
         {   
             ident=wait(&st1);
             st1=st1>>8;
             printf("Tym razem to ja, rodzic.\n");
             printf("Potomek %d podal kod wyjscia %3d\n",ident,st1);
         }    
}   
