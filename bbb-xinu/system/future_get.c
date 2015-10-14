#include <future.h>

syscall future_get(future* fut, int* value)
{
	

	if(fut->state == FUTURE_VALID)            /* value is already produced */
	{
		*value = fut->value;              /* reading the fut->value to value pointer */
              
		return 1;	
	}
	else if(fut->state == FUTURE_EMPTY)       /* value is not yet produced */
	{
		fut->state = FUTURE_WAITING;      /* going to waiting  until value get produced */
		fut->pid = currpid;  
                return 0;
	}
	else if(fut->state == FUTURE_WAITING)
	{
	
	return -1;
	}
}
