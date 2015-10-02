
#include <prodcons.h>
#include <stdlib.h>

int n;
sid32 consumed,produced;
int isNumeric(const char *str) ;
            
//Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/


shellcmd xsh_prodcons(int nargs, char *args[])
{
	int count = 2000;             //local varible to hold count
        //Argument verifications and validations
	
	consumed = semcreate(1);
	produced = semcreate(0);

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
	printf("Use: %s Command\n", args[0]);
	printf("Description: Producer-Consumer \n");
	printf("\t--help\t To implement the producer-consumer problem\n");
	return 0;
	}

       
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
	printf("Too many Arguments\n");
	return 0;
	}
	
	
	resume( create(producer, 1024, 20, "producer", 1, count) );
        resume( create(consumer, 1024, 20, "consumer", 1, count) );
       

     
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
	
