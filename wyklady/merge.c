/* To jest wersja chodzaca (byc moze jeszcze niedoskonala) */

#include <stdio.h>
#include <unistd.h>

int a[150];

merge(p,r,q)
   int p,r,q;
   
   {
      int b[150];
      int k,l,m;
      
      k=p;
      l=r+1;
      m=0;
      while (k<=r || l<=q)
         if (k<=r && l<=q)
            if (a[k]<a[l])
               b[m++]=a[k++];
            else 
               b[m++]=a[l++];
         else
            if (k<=r)
               b[m++]=a[k++];
            else
               b[m++]=a[l++];
      for (k=p; k<=q; k++)
         a[k]=b[k-p]; 
   }                           

sort(p,q)
   int p,q;
   
   {
      int r,x;
      int fd[2];
      
      if (p<q)
         {
            r=(p+q)/2;
            x=4*(r-p+1);
            pipe(fd);
            if (fork()==0)
               {
                  close(fd[0]);
                  sort(p,r);
                  write(fd[1],&a[p],x);
                  close(fd[1]);
                  exit(0);
               }
            else
               {               
                  close(fd[1]);   
                  sort(r+1,q);
                  read(fd[0],&a[p],x);
                  close(fd[0]);
                  wait();
               }
            merge(p,r,q);                      
         }
   }                     
           
main()
{ 
   int i,n;
   
   printf("Ile bedzie liczb w ciagu ? ");
   scanf("%3d",&n);
   printf("Podaj te liczby: \n");
   for (i=0; i<n; i++)
      {
         printf("a[%3d]=",i);
         scanf("%8d",a+i);
      }
      
   sort(0,n-1);   
      
      
   printf("Ciag posortowany: \n");
   for (i=0; i<n; i++)
      printf("%8d\n",a[i]);
}            
