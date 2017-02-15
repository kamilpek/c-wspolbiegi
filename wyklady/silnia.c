#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

main()
   {
      int fd[2],pass,i,n;
      
      printf("Podaj n: ");
      scanf("%d",&n);
      pipe(fd);
      printf("Lacze utworzone \n");
      if(fork()==0)
         {printf("Zglasza sie proces potomny \n");
          close(fd[0]);
          pass=1;
          for(i=1; i<=n; i++)
             pass*=i;
          printf("Wartosc wysylana z potomka: %5d\n",pass);   
          write(fd[1],&pass,sizeof(pass));}
      else
         {printf("Zglasza sie proces macierzysty \n");
          close(fd[1]);
          read(fd[0],&pass,sizeof(pass));
          printf("Wartosc silni: %5d\n",pass);}
    }        
