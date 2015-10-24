#include<prodcons.h>

uint future_cons(future *fut) {

	
	int i, status;

	
	status = future_get(fut, &i);

	if (status < 1) {
		printf("future_get failed\n");
		return -1;
	}
	
	printf("It produced : %d \n", i);
	if(fut->flag == FUTURE_EXCLUSIVE){
		
		future_free(fut);		
		
		return OK;
	}
	if(q_isempty(fut->get_queue)){
		
		future_free(fut);
		
	}
	
	return OK;
}
