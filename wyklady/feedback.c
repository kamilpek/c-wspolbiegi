#include <stdio.h>
main()
   {
      int n,k;
      
      printf("Podaj liczbe: ");
      scanf("%3d",&n);
      if (fork()==0)
         {exit(n);}
      else
         {wait(&k);
          k=k>>8;
          printf("Oto liczba: %3d\n",k);}
   }  
