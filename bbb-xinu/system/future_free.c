#include <future.h>

syscall future_free(future* fut)
{

 int retValue=0;
 retValue = freemem(fut,sizeof(future));  
   
       if(retValue==SYSERR)
      {
        return SYSERR;
      }
return OK;
}
