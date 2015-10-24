#include <future.h> 

/* if future has value return */
syscall future_get(future *f, int *value){
	intmask	mask;
	mask=disable();
	pid32 p_id;	
	if (f->state == FUTURE_VALID){
   	 	*value = f->value;
		restore(mask);
    		return OK;
 	}
	if(f->state == FUTURE_EMPTY){
		f->state=FUTURE_WAITING;
		if(f->flag == FUTURE_EXCLUSIVE){
			f->pid=currpid;
			suspend(f->pid);
			*value = *f->value;
			restore(mask);
			return OK;
		}else if(f->flag == FUTURE_SHARED){	
			f->state=FUTURE_WAITING;			
			p_id = f_enqueue(currpid, f->get_queue);
			if(p_id == (pid32) SYSERR){
				restore(mask);
				return SYSERR;
			}				
			suspend(currpid);
			*value = *f->value;
			restore(mask);
			return OK;	
		}
		else if(f->flag == FUTURE_QUEUE){
			if(!q_isempty(f->set_queue)){
				*value = *f->value;
				resume(f_dequeue(f->set_queue));
			}else{	
				f->state=FUTURE_WAITING;			
				p_id = f_enqueue(currpid, f->get_queue);
				if(p_id == (pid32) SYSERR){
					restore(mask);
					return SYSERR;
				}				
				suspend(currpid);
				*value = *f->value;
			}
			restore(mask);
			return OK;	
		}
	}

	if(f->flag == FUTURE_SHARED && f->state==FUTURE_WAITING){
		p_id = f_enqueue(currpid, f->get_queue);
		if(p_id == (pid32) SYSERR){
			restore(mask);
			return SYSERR;
		}	
		suspend(currpid);
		*value = *f->value;
		restore(mask);
		return OK;	
	}

	if(f->flag == FUTURE_QUEUE && f->state==FUTURE_WAITING){
		if(!q_isempty(f->set_queue)){
			resume(f_dequeue(f->set_queue));
		}else{
			p_id = f_enqueue(currpid, f->get_queue);
			if(p_id == (pid32) SYSERR){
				restore(mask);
				return SYSERR;
			}	
			suspend(currpid);
			*value = *f->value;
		}
		
		restore(mask);
		return OK;	
	}


 	restore(mask);
  	return SYSERR;
}
