#include <newmem.h>
#include<string.h>

 void testprocess()
{		
        fact(6);
	printf("Process Ends..\n");
	killme(currpid);

}
int fact(int count)
{
	if(count ==0||count ==1)
	{
	return 1;
	}
	else
	{
	return count*fact(count-1);
	}
	
}
