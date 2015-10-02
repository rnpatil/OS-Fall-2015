#include <prodcons.h>


 void consumer(int count)
 {
	int j ;
     //Code to consume values of global variable 'n' until the value of n is less than or equal to count
     //print consumed value e.g. consumed : 8
     
	for(j = 1;j<=count;j++)
	{
	wait(produced);
	printf("Consumed Value :%d\n",n);
	signal(consumed);
	}
	printf("Ending the program, semaphores deleted..");
	semdelete(produced);
	semdelete(consumed);
     
 }
