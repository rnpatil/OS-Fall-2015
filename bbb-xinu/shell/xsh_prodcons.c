#include <prodcons.h>

int n;
sid32 consumed,produced;
future *f1, *f2, *f3;
int isNumeric(const char *str) ;
int flag =0;
future *f_exclusive, *f_shared, *f_queue;
struct memblk* memptr;

//Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/


shellcmd xsh_prodcons(int nargs, char *args[])
{
	int count = 2000;             //local varible to hold count
        //Argument verifications and validations

 	f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
  	f_shared = future_alloc(FUTURE_SHARED);
  	f_queue = future_alloc(FUTURE_QUEUE);
	
	consumed = semcreate(1);
	produced = semcreate(0);

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
	printf("Use: %s Command\n", args[0]);
	printf("Description: FUTURE IMPLEMENTATION PART 2 \n");
	printf("\t--help\t To implement the producer-consumer problem with the use of FUTURES with queue implementations\n");
	return 0;
	}

       
	if(nargs==2 && strcmp(args[1], "-f") == 0)
	{
	flag=1;
	}
	else if(nargs==2 && strcmp(args[1], "-n") == 0)
	{
	flag=2;
	}

if(flag == 0)
{
       if(nargs==2)
        {
	if (isNumeric(args[1])==1)
	 {
         count=atoi(args[1]);
	 }	
	else 
	 {
	  printf("Enter a valid  number!\n");
                        return 0;
        }
        }
        
	else if (nargs>2)
	{
	printf("Too many Arguments!!\n");
	return 0;
	}
	


	

	resume( create(producer, 1024, 20, "producer", 1, count) );
	resume( create(consumer, 1024, 20, "consumer", 1, count) );

}

if (flag ==1)
{     
	//Futures Implementation
	
 
	  	 
	// Test FUTURE_EXCLUSIVE
	  resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
	  resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
          sleep(1);
	// Test FUTURE_SHARED
	  resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
	  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
	  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
	  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
	  resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) ); 
           sleepms(10);
	// Test FUTURE_QUEUE
	  resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
	  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
	  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
	  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
	  resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
	  resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
	  resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
	  resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );

        flag =0;

}

if (flag ==2)
{

	  resume( create(net_consumer, 1024, 20, "net_consumer", 1, f_exclusive) );
	  resume( create(net_producer, 1024, 20, "net_producer", 1, f_exclusive) ); 
flag =0;
}

      //check args[1] if present assign value to count

      //create the process producer and consumer and put them in ready queue.
      //Look at the definations of function create and resume in xinu/system folder for reference.      
  return 0;   
}



int isNumeric(const char *str) 
	{
	 while(*str != '\0') 
		{ 
			if(*str < '0' || *str > '9') 
			return 0; 
			str++; 
		} 
	return 1;
	 }
	
