
#include <future.h>

future* future_alloc(int future_flags)
{
	future* fut;
    	
	
    	fut = (future*) getmem(sizeof(future)); /*allocating memory to the future*/
 
       	if (SYSERR == (int)fut)    		/* safety check*/
    	{
	return NULL;
    	}

	else{
	fut->state = FUTURE_EMPTY;	/*Initializing the future state to FUTURE_EMPTY */
	fut->flag = future_flags;	/*Initializing the future flag to future_flags */
	return fut;
	} 

	
    	
}
