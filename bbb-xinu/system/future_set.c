#include <future.h>

syscall future_set(future* fut, int value)
{
	
	if(fut->state == FUTURE_EMPTY)	    /*set the value of the future with produced value and change the status to FUTURE_VALID*/
	{
		fut->state = FUTURE_VALID;
		fut->value= value;		
	}	
	else if(fut->state == FUTURE_WAITING)	
	{
                fut->state = FUTURE_VALID;	
		fut->value = value;			
	}
	else if(fut->state == FUTURE_VALID)	
        {
	return SYSERR;
        }
return OK;
}

