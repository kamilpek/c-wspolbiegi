#include <stdio.h>
#include <fcntl.h>

main()
   {
      int a,i,fd;

      fd=open("queue",O_WRONLY,0);
      for (i=0; i<5; i++)
         {
            printf("Podaj liczbe: ");
            scanf("%3d",&a);
            write(fd,&a,4);
         }
      close(fd);
   }
