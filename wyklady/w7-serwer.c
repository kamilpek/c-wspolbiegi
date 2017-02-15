
#include <stdio.h>
#include <fcntl.h>

main()
   {
      int a,i,fd;

      fd=open("queue",O_RDONLY,0);
      for (i=0; i<5; i++)
         {
            read(fd,&a,4);
            printf("Odebralem %4d\n",a);
         }
      close(fd);
   }
