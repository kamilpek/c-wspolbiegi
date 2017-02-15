#include <sys/types.h>
#include <sys/socket.h>

main()
{
   int fv[2];
   char bufor[256];
   
   socketpair(PF_UNIX, SOCK_STREAM, 0, fv);
   if (fork()==0)
      {close(fv[1]);
       read(fv[0],&bufor,256);
       printf("Zglasza sie proces potomny.");
       printf("Odebralem: %s\n",bufor);
       close(fv[0]);
       exit(0);}
   else
      {close(fv[0]);
       printf("Zglasza sie proces rodzicielski.");
       printf("Podaj lancuch: \n");
       scanf("%s",bufor);
       write(fv[1],&bufor,256);
       close(fv[1]);
       wait();
       exit(0);}
} 
