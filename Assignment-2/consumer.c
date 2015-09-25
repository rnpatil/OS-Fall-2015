#include <prodcons.h>


 void consumer(int count)
 {
	int j ;
     //Code to consume values of global variable 'n' until the value of n is less than or equal to count
     //print consumed value e.g. consumed : 8
	for(j = 0;j<count;j++)
	{
		printf("Consumed Value :%d\n",n);
		
	}
 }
