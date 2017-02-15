main()
{ 
   int childpid;
   
   if ((childpid = fork())==-1) printf("no fork");
      else if (childpid==0) {printf("child"); exit(0);}
               else {printf("parent");exit(0);}
}                          
