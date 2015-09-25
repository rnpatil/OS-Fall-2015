
#include <prodcons.h>
#include <stdlib.h>

int n;                 
//Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/
int isNumeric(const char *str) ;
shellcmd xsh_prodcons(int nargs, char *args[])
{
      //Argument verifications and validations
	
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
	printf("Use: %s Command\n", args[0]);
	printf("Description: Producer-Consumer \n");
	printf("\t--help\t To implement the producer-consumer problem\n");
		return 0;
	}

       int count = 2000;             //local varible to hold count
       if(nargs==2)
        {
	if (isNumeric(args[1])==1)
	{
         count=atoi(args[1]);
		
	 resume( create(producer, 1024, 20, "producer", 1, count) );
      resume( create(consumer, 1024, 20, "consumer", 1, count) );
	}	else	{
			printf("Not a number!");
}
        }	else        if(nargs==1)	{
		resume( create(producer, 1024, 20, "producer", 1, count) );
      resume( create(consumer, 1024, 20, "consumer", 1, count) );
}
      //check args[1] if present assign value to count

      //create the process producer and consumer and put them in ready queue.
      //Look at the definations of function create and resume in xinu/system folder for reference.      
     
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
	
