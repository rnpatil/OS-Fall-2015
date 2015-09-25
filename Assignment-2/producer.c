#include <prodcons.h>


 void producer(int count)
 {
	int i ;
      //Code to produce values less than equal to count 
      //produced value should get assigned to global variable 'n'.
      //print produced value e.g. produced : 8
	for( i = 0;i<count;i++)
	{
		n=i;
		printf("Produced value : %d\n", n);
		
	}
 }
