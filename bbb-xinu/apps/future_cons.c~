#include <prodcons.h>

uint future_cons(future *fut) {

  int i, status=0;

 while(1)
{
  status = future_get(fut, &i);  /* First get the produced value from producer */


  if (status < 1)  /*Producer isnt yet ready with the produced value*/
  {
   continue;
  }
 
  else if (status == 1) {
   printf("Consumed Value : %d \n",i);  /*Print the produced value*/
    break;

  }

 }     
  return OK;
}
